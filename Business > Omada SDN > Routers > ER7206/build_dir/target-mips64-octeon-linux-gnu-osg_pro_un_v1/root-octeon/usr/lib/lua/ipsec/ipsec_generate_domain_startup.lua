LuaQ               B      A@   E     \    Αΐ   Ε    ά   AA  E   \ ΑA  ΖΒ  J B bB ά@δ           Η δA           ΗΑ ΖΓά B CAΒ  E B Α   \B KΒD\B FΓ\  BEΑ  ΖΒE  άB ΐ  MΓC άB         require    luci.model.uci    luci.tools.debug 	   luci.sys    socket    luci.tools.error    luci.tools.form    cursor    Form    name $   generate_ipsec_check_dns_from_ipsec ,   generate_ipsec_check_dns_from_ipsec_secrets    gettime    io    open    /etc/config/ipsec_check_dns    w+    ipsec    connection    close    string    format +   /lib/ipsec/ipsec_generate_domain.sh unlock 
   fork_call +   generate ipsec_check_dns time:t2 - t1 is [    ]           `    ½   Κ     @  ΐ $             A B    ΕA   ά@) B    ΐWΐ@ ΐ A A   A A  EΓ FΒC ΖΒ\A  AΓ A Fΐΐΐΐ @   @ C @ Γ BΑ    @ Γ BΑΓ   @ Γ BΑ DΔ@  @ Γ BΑΓ Β@  B   FΐC CΕWΐ@ CΕ Aΐ  AC A  A A  EΓ FΒC ΖΕ\A  AΓ ACΕΐ@ΐ   A A   AC A  EΓ FΒ ΐ  \A  EΓ FΒΓ ΐ \A  EΓ FΒ ΖCΔ\A  EΓ FΒΓ \ A  EΓ FΒΓ ΖΒ\A  EΓ FΒ \ A   FCΕC W F@  Ζΐ CF Cΐ EΓ FΒ ΐ DΔ\ C  α  ΐΥΒ ή         foreach    ipairs    local_binding_type    domain_name    if_name    
    config domain
    string    format    	option domain_name '%s'
    local_binding &   	#1: DOMAIN_NORMAL,2: DOMAIN_SPECIAL
    	option domain_type '1'
    	option domain_type '2'
    	option binding_file '%s'
 #   	option binding_section_type '%s'
    	option binding_item  '%s'
    name (   	option binding_field  'local_binding'
 $   	option tunnel_local_binding  '%s'
 "   	option old_ipaddr	'xx.xx.xx.xx'
    remote_peer_type    remote_peer &   	option binding_field  'remote_peer'
    write    convert %s "%s" err!                  D         @Δ  Λ@ΐD @ ά Iΐ D        F Z@  ΐ B    ΐ@^      	      get_all    .name    ERR_COM_TABLE_ITEM_UCI_GET                                 b   ?    ±   Κ     @  ΐ $             A B    ΕA   ά@& B    ΐWΐ@ ΐ A@A   A A  EΓ FΒC ΖΒ\A  AΓ Aΐΐ@ΐ   A A   AC A  EΓ FΒ ΐ  \A  EΓ FΒΓ ΐ \A  EΓ FΒ ΖCΔ\A  EΓ FΒ \ A  EΓ FΒΓ ΖΒ\A  A AB CΕWΐ@ CΕ A   A A  A A  EΓ FΒC ΖΓΕ\A  AΓ ACΕΐ@ΐ   A A   AC A  EΓ FΒ ΐ  \A  EΓ FΒΓ ΐ \A  EΓ FΒ ΖCΔ\A  A A  EΓ FΒΓ ΖΒ\A  A A W@F@ @Ζΐ F Cΐ EΓ FΒΓ ΐ DΔ\ C  α  ΐΨΒ ή         foreach    ipairs    local_id_type    IP_ADDRESS_FROM_DNSNAME    IP_ADDRESS_FROM_IFNAME    
    config domain
    string    format    	option domain_name '%s'
    local_id_value &   	#1: DOMAIN_NORMAL,2: DOMAIN_SPECIAL
    	option domain_type '1'
    	option domain_type '2'
    	option binding_file '%s'
 #   	option binding_section_type '%s'
    	option binding_item  '%s'
    name )   	option binding_field  'local_id_value'
 $   	option tunnel_local_binding  '%s'
 "   	option old_ipaddr	'xx.xx.xx.xx'
    remote_id_type        remote_id_value *   	option binding_field  'remote_id_value'
    write    convert %s "%s" err!        g   l       D         @Δ  Λ@ΐD @ ά Iΐ D        F Z@  ΐ B    ΐ@^      	      get_all    .name    ERR_COM_TABLE_ITEM_UCI_GET                                         