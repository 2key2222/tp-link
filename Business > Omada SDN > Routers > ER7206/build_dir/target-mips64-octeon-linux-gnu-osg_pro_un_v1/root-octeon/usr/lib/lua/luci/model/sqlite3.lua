LuaQ               E      A@  ??  ??@@?@ A? ?   @ A? ? A@ G  A? G? E  F ? \?? G  E  K?? ?  \??G@ d   G? d@  G  d?  G@ d?  G? d  G? d@ G  d? G@ d? G? d  G? d@ G  d? G@ d?     G? d  G? d@ G  d? G@ d?     G? d      G? d@ G  d? G@ d? G?  ? #      module    luci.model.sqlite3    package    seeall    sqlite3    require    luasql.sqlite3    luci.tools.debug    usermngrDbName    /etc/config/user.db    usermngrTableName 	   usermngr    dbenv    dbcon    connect    stringSplit    createUsermngrTable    createUsermngrTableTmp    createWportalTable    createWifiTable    createWechatTable    insertEntry 	   delEntry 	   getEntry    getAuthEntry    sqlExe    sqlExeWithTransaction    delAllEntry    updateEntry    curUserMinus    printAllEntry    printEntry    copyTab    getAllByCmd    test                
   W @ ? ?W@@ @ ? ? @ ??  ?  ?   ?    ? ? ?ˀ?A?  ?? U??? ? ?? ?A?  @ ?A??@   ??   ?            gmatch    (.-)    table    insert                        <     2   ?   ? @??? ?@@@  ܀??  ?@A ?? ??KA?? \?????? A ?? ?A??A Ł   ܁ ????Ł  ??? @? ܁? ??A?@ ???? ?A ?A?E?  F???? ?? \???  ? ?A ?A??A ?AB?A  ?       sqlite3    connect    string    format H   select count(*) from sqlite_master where type = 'table' and name = '%s'    execute    fetch    row    a    close 	   tonumber 	    ?  CREATE TABLE %s(
		userType	VARCHAR(10),
		userName 	VARCHAR(100) PRIMARY KEY,
		password   	VARCHAR(100),
		expireTime	VARCHAR(20),
		validPeriod 	VARCHAR(20),
		maxUser	INTEGER,
		upBand	INTEGER,
		downBand	INTEGER,
		macBindType	VARCHAR(10),
		macBindAddr	VARCHAR(100),	
		noteName   	VARCHAR(100),
		noteTel   	VARCHAR(100),
		noteNote   	VARCHAR(100),
		enable		VARCHAR(10),
		curUser	INTEGER
		)    status    errorString ,   create index index_usermngr on %s(userName)                     >   `     2   ?   ? @??? ?@@@  ܀??  ?@A ?? ??KA?? \?????? A ?? ?A??A Ł   ܁ ????Ł  ??? @? ܁? ??A?@ ???? ?A ?A?E?  F???? ?? \???  ? ?A ?A??A ?AB?A  ?       sqlite3    connect    string    format H   select count(*) from sqlite_master where type = 'table' and name = '%s'    execute    fetch    row    a    close 	   tonumber 	      CREATE TABLE %s(
		userType	VARCHAR(10),
		userName 	VARCHAR(100) PRIMARY KEY,
		password   	VARCHAR(100),
		expireTime	VARCHAR(20),
		validPeriod 	VARCHAR(20),
		maxUser	INTEGER,
		upBand	INTEGER,
		downBand	INTEGER,
		macBindType	VARCHAR(10),
		macBindAddr	VARCHAR(100),	
		noteName   	VARCHAR(100),
		noteTel   	VARCHAR(100),
		noteNote   	VARCHAR(100),
		enable		VARCHAR(10)
		)    status    errorString ,   create index index_usermngr on %s(userName)                     b   ?     2   ?   ? @??? ?@@@  ܀??  ?@A ?? ??KA?? \?????? A ?? ?A??A Ł   ܁ ????Ł  ??? @? ܁? ??A?@ ???? ?A ?A?E?  F???? ?? \???  ? ?A ?A??A ?AB?A  ?       sqlite3    connect    string    format H   select count(*) from sqlite_master where type = 'table' and name = '%s'    execute    fetch    row    a    close 	   tonumber 	    
  CREATE TABLE %s(
			name			VARCHAR(100),
			gw_id			VARCHAR(20),
		    	enable            		VARCHAR(16),
			interface          		VARCHAR(32),
			wportal_page_type  	VARCHAR(16),
			page_title         	VARCHAR(100),
			wel_info           		VARCHAR(100),
			copyright          		VARCHAR(100),
            background         VARCHAR(64),
			external_url       	VARCHAR(256),
			external_url_succ  	VARCHAR(256),
			external_url_fail  	VARCHAR(256),
			wportal_type	   	VARCHAR(16),
			remind_enable      	VARCHAR(16),
			remind_time        	INTEGER,
			remind_type        	INTEGER,
			remind_interval    	INTEGER,
			remind_page_title  	VARCHAR(256),
			remind_page_content VARCHAR(256),
			first_server_ip    	VARCHAR(100),
			second_server_ip   	VARCHAR(100),
			portal_port        	INTEGER,
			share_key          	VARCHAR(120),
			send_count         	INTEGER,
			expire_time        	INTEGER,
			auth_type          	VARCHAR(100),
			free_interval      	INTEGER,
			portal_type		VARCHAR(16),
            wired_auth      VARCHAR(16)
		)    status    errorString ,   create index index_wportal on %s(interface)                     ?   ?     2   ?   ? @??? ?@@@  ܀??  ?@A ?? ??KA?? \?????? A ?? ?A??A Ł   ܁ ????Ł  ??? @? ܁? ??A?@ ???? ?A ?A?E?  F???? ?? \???  ? ?A ?A??A ?AB?A  ?       sqlite3    connect    string    format H   select count(*) from sqlite_master where type = 'table' and name = '%s'    execute    fetch    row    a    close 	   tonumber 	    ?  CREATE TABLE %s(
            name                    VARCHAR(100),
            gw_id                   VARCHAR(20),
            enable                  VARCHAR(16),
            interface               VARCHAR(32),
            ssid                    VARCHAR(32),
            free_interval           INTEGER,
            authToken               VARCHAR(32),
            welinfo                 VARCHAR(200),
            logoinfo                VARCHAR(200),
            btninfo                 VARCHAR(200),
            appid                   VARCHAR(64),
            shopid                  VARCHAR(64),
            secretkey               VARCHAR(64),
            extend                  VARCHAR(64),
            mac                     VARCHAR(18),
            bssid                   VARCHAR(32),
            portal_type             VARCHAR(16),
            background              VARCHAR(64),
            logo                    VARCHAR(64),
            copyright               VARCHAR(200),
            wired_auth              VARCHAR(16),
            logoname                VARCHAR(192),
            bgdname                 VARCHAR(192)
        )    status    errorString (   create index index_wportal on %s(gw_id)                     ?   ?     2   ?   ? @??? ?@@@  ܀??  ?@A ?? ??KA?? \?????? A ?? ?A??A Ł   ܁ ????Ł  ??? @? ܁? ??A?@ ???? ?A ?A?E?  F???? ?? \???  ? ?A ?A??A ?AB?A  ?       sqlite3    connect    string    format H   select count(*) from sqlite_master where type = 'table' and name = '%s'    execute    fetch    row    a    close 	   tonumber 	    $  CREATE TABLE %s(
			name			VARCHAR(100),
			gw_id			VARCHAR(20),
		    	enable             		VARCHAR(16),
            pcfree             		VARCHAR(16),
			interface          		VARCHAR(32),
			free_interval      	INTEGER,
            			authToken           	VARCHAR(16),
			publicName         	VARCHAR(100),
			qrcodeImage           	VARCHAR(100),
			wechatInfo          	VARCHAR(256),
			copyright		VARCHAR(100),
			jumpPageType       	VARCHAR(20),
			portal_type          	VARCHAR(20),
			adImage  		VARCHAR(256),
			remoteUrl  		VARCHAR(256)
		)    status    errorString ,   create index index_wportal on %s(interface)                     ?   ?        E  F?\?? ?A?   ???Ł  ??? @? ? ܁ ? ?ˁA@????B  ???A?A ????A   ?       sqlite3    connect    string    format    INSERT INTO %s VALUES (%s)    errorString    execute    close                     ?          E  F?\?? ?A?   ???Ł  ??? @? ?BAƂA܁?? ??B@?????  ??AB?A ?A??A   ? 
      sqlite3    connect    string    format    DELETE FROM %s where %s = '%s'    key    value    errorString    execute    close                           "   ?   ? ?܀? A??  ??C??  ?@A ?? ?BA?A??@ ?A????? ?  ??B?  ?B ? ? ?BB ?BB ??B ?  ?       sqlite3    connect    string    format     SELECT *FROM %s where %s = '%s'    key    value    execute    fetch    a    close                       /    "   ?   ? ?܀? A??  ??C??  ?@A ?? ?BA?A??@ ?A????? ?  ??B?  ?B ? ? ?BB ?BB ??B ?  ?       sqlite3    connect    string    format /   SELECT *FROM %s WHERE ip = '%s' and mac = '%s'    ip    mac    execute    fetch    a    close                     2  ?       ?   ? ?܀? A??  ??K?@?? \????  ? ?KA\A K?\A @ ??  ^? ?       sqlite3    connect    errorString    execute    close                     B  [   @   ? ? ?   ? ?܀? A??  ??E?  ?? \? ??@ ?Z@  ? ?J? ?? bA? @ ?KA?  \A?EA ?? \ ??  ???B ??A ??ǂ ?  ?  ? ? ?B??? W@B@??  ?? ?B ??B?? ǂ ?  ?  ł ??a?   ?KC\? ?? ? ?KAC\A KA?\A @ ?? ^? ?       sqlite3    connect    type    table    setautocommit    ipairs    errorString    execute    errorString:      sql execute failed,rollback 	   rollback    commit    close                     ]  r    +     @?? KA@Ł  \????  ?A?A ? ????  ???  ????BEB ?? ܁ ?BB  @?? W@C???  AA? ?? ???  ??? G? ?  ??B ?BB ?   ?       sqlite3    connect    dbName    string    format H   select count(*) from sqlite_master where type = 'table' and name = '%s' 
   tableName    execute    fetch    row    a    close 	   tonumber 	       delete *FROM %s    err                     t  ?    J     @?? KA@?  \????  ??@?  ? FBA??A?????@ ܁??? ?? ˁ?J  ?? ܁ ?A ? B ܁ W@?@??A W?????A ?  ??Ł  ???? @? ?BAƂA܁?????@ ???B ? ?? ˁ?EB ?? ܁ ?A  ?Ł  ???? @? ??܁ ????@ ???B ? ?? ????A ????A ??D?A  ?       sqlite3    connect    string    format !   select* from  %s WHERE %s = '%s'    key    value    cursor    execute    row    fetch    a 	   tonumber 	        DELETE FROM %s where %s = '%s'    res    errorString    INSERT INTO %s VALUES (%s)    close                     ?  ?    Q   ?   ? ?܀? A??  ??E?  F??? ?? BAF?A\???B ?????? ?? ??B
  A? ?? ?A ? ?A ?? W@C@
??A W?C?	??A ?  ??? ?A ????? ???@??A ?A ?????????@ ??A ?AÇ??  ??@?A  ? EB F???BAƂA?? @ ?B ?????? ?? ?? ??BB A? ?? ?A  ??? ?E?A ?E?A ???A ?? ?? ?? ?       sqlite3    connect    string    format !   select* from  %s WHERE %s = '%s'    key    value    cursor    execute    row    fetch    a 	   tonumber 	        curUser 	   )   update %s set curUser = %d where %s='%s'    res    errorString    close                     ?  ?   
=   ?   ? @??? ?@@@  ܀??  K??A Ɓ?? @? ??\  ?  ?    A A ?  ?B?  ?? ? A  EA ? W@C??A W?C ?A   @?? EA A ?  ?B?A ?? ? A ??  A A ? ?  AA A ?  ?DA ??A ?DA  ?       sqlite3    connect    cur    assert    execute    string    format    		SELECT *FROM %s    print table start...    row    fetch    a 	   tonumber 	        printEntry    print table end... #   no entry found,the table is empty!    close                     ?  ?      D   F ? ?   \@  ?    
   dumptable                     ?  ?    	   J   ?   ?@    ??   ? ???A    ܁ W??@ ?I??? ???    ܁ I????  ??^   ?       pairs    type    table    copyTab                     ?      
7   ?   ? ?܀? A??  ??J  ? ?AA@ ????  ??  ??  ??  ??A
  A ?? ?? ?A Ł ?? W?B???? W?B ??? ?  ?????C?A ? ܁ I???  ??A? A ?? ?? ??  ?C???  ??C?A ??C?A ????A ^  ?       sqlite3    connect    cur    errStr    assert    execute    row    fetch    a 	   tonumber 	     	      copyTab    close                       "     	   
?  	@@?	?@?	@A?E? ?? ?   \@? ?    	   userName    123 	   password    xxx    macAddr    22-22-22-22-22-22    local_auth 	   usermngr                             