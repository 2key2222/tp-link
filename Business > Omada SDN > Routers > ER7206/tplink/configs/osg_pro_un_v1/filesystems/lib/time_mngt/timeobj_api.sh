# Copyight(c) 2008-2015 Shenzhen TP-LINK Technologies Co.Ltd.
# file     timeobj_api.sh
# bief     The Api for timeobj
# author   Yuan Fengjia
# vesion   1.0.0
# history  1.0.0, 13May15, Yuanfengjia, Ceate the file

. /lib/functions.sh

_timeobj_init_deleteAll() {                                        
    local timeobj="$1"                                                                                                        
                                                                                                             
    local ref=$(uci_get time_mngt "$timeobj" ref)
    for i in $ref
    do 
        uci delete time_mngt.$i
        uci del_list time_mngt.$timeobj.ref=$i
        uci_commit time_mngt                        
    done                                                                           
}

timeobj_init_deleteAll() {
     config_load time_mngt
	 config_foreach _timeobj_init_deleteAll entry
	 
}

_timeobj_add() {
    local timeobj="$1"
    local timeobj_name="$2"
    local module="$3"
    local rule_name="$4"

    local name
    local time_t
    local new="true"
	local ret
    name=$(uci_get time_mngt "$timeobj" entry_name)
    [ "$name" == "$timeobj_name" ] && {
        time_t=$(uci_get time_mngt "$timeobj" slots)                  
        ret=$(tmngtd-control -a "$module"  "$timeobj_name" "$time_t" "$rule_name")
		if [ "$ret" == "Error occured" ]; then
		    echo "Error occured"
		    return 0
		fi
     
        local ref=$(uci_get time_mngt "$timeobj" ref)
        for i in $ref
        do 
            local module_name=$(uci_get time_mngt "$i" module)
            if [ $module_name == $module ]; then
                local use=$(uci_get time_mngt "$i" use)
                use=$((use+1)) 
                uci_set time_mngt "$i" use "$use"           
                uci_commit time_mngt  
                new="false"
                break
            fi
        done     
        
        if [ $new == "true" ]; then
            #local tmp=$(date +%s%N)
            local tmp=$(openssl rand -base64 32 | md5sum | cut -c1-16)
            uci set time_mngt.$tmp=ref
            uci_set time_mngt $tmp module $module
            uci_set time_mngt $tmp use 1
            uci_add_list time_mngt $timeobj ref $tmp
            uci_commit time_mngt
        fi
    }                                                 
}                                                          
                                                                                                                   
_timeobj_delete() {                                        
    local timeobj="$1"                                     
    local timeobj_name="$2"                                  
    local module="$3"  
    local rule_name="$4"	
                                                             
    local name                                               
    local time_t            
    local ret	
    name=$(uci_get time_mngt "$timeobj" entry_name)                                              
    #echo "timeobj_name=$timeobj_name,module=$module,rule_name=$rule_name,name=$name" >> /tmp/timeobj.log	
    [ "$name" == "$timeobj_name" ] && {      
        local ref=$(uci_get time_mngt "$timeobj" ref)
        for i in $ref
        do 
            local module_name=$(uci_get time_mngt "$i" module)
            if [ $module_name == $module ]; then
			    time_t=$(uci_get time_mngt "$timeobj" slots)                                
                ret=$(tmngtd-control -d "$module" "$timeobj_name" "$time_t" "$rule_name")
				if [ "$ret" == "Error occured" ]; then
				    echo "Error occured"
		            return 0
		        fi
				
                local use=$(uci_get time_mngt "$i" use)
				#echo "use=$use" >> /tmp/timeobj.log
                use=$((use-1)) 
				#echo "use2=$use" >> /tmp/timeobj.log
                uci_set time_mngt "$i" use "$use"           
                uci_commit time_mngt  
                [ $use == 0 ] && {     
                    uci delete time_mngt.$i
                    uci del_list time_mngt.$timeobj.ref=$i
                    uci_commit time_mngt                       
                } 
				#echo "commit" >> /tmp/timeobj.log
				#time_t=$(uci_get time_mngt "$timeobj" slots)                                
                #tmngtd-control -d "$module" "$timeobj_name" "$time_t" "$rule_name"
                break
            fi
        done                      
    }                                                         
}

_timeobj_deleteAll() {                                        
    local timeobj="$1"                                                                   
    local module="$2"                                        
                                                                                                             
    local ref=$(uci_get time_mngt "$timeobj" ref)
    for i in $ref
    do 
        local module_name=$(uci_get time_mngt "$i" module)
        if [ $module_name == $module ]; then
            uci delete time_mngt.$i
            uci del_list time_mngt.$timeobj.ref=$i
            uci_commit time_mngt                        
        fi
    done                                                                           
}
#Add timeobj 
#timeobj_api_add <timeobj_name> <module_name> <rule_name>                                          
timeobj_api_add() {                                        
    local timeobj_name="$1"                                
    local module="$2" 
    local rule="$3"                                     
                                                                                               
	{
		flock -x 20
    config_load time_mngt                                     
    config_foreach _timeobj_add entry $timeobj_name $module $rule
		flock -u 20
	} 20<>/tmp/timeobj.lock
}                                                  
 
#Delete timeobj     
#timeobj_api_delete <timeobj_name> <module_name> <rule_name>                                           
timeobj_api_delete() {                                                                                            
    local timeobj_name="$1"                                   
    local module="$2"     
    local rule="$3" 	
                                                              
	{
		flock -x 20
    config_load time_mngt                                     
    config_foreach _timeobj_delete entry $timeobj_name $module $rule
		flock -u 20
	} 20<>/tmp/timeobj.lock
}   

#Delete all timeobj from the module
#timeobj_api_deleteAll<module_name>
timeobj_api_deleteAll() {
    local module="$1"
    
    {
		flock -x 20
	local ret 
	ret=$(tmngtd-control -D "$module")
	if [ "$ret" == "Error occured" ]; then
	    echo "Error occured"
			flock -u 20
		return 0
    fi
    config_load time_mngt                                     
    config_foreach _timeobj_deleteAll entry $module
		flock -u 20
    } 20<>/tmp/timeobj.lock
     
}                     
#Commit the operation
#timeobj_api_commit<module_name>
timeobj_api_commit() {
    local module="$1"
    {
		flock -x 20
    tmngtd-control -u "$module"
		flock -u 20
	} 20<>/tmp/timeobj.lock
}
