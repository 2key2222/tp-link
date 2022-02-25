/*
 *  Copyright (c) 2014  TP-LINK Co., Ltd
 *
 *  TP-LINK Co., Ltd R&D SMB Product Line
 *
 */

#include <common.h>
#include <command.h>
#include "dt_common.h"

extern int   autoboot_enable(uint32_t enable);
extern ulong dram_mtest_quick(vu_long *, ulong, ulong, vu_long, int);

/* Set of available Memory tests. */
testDesc tests_pattern[] = {
    { "Address Rot",           dram_addr_rot,         0xFFFF,   8, 0, 0},
    { "Address ~Rot",          dram_com_addr_rot,     0xFFFF,   8, 0, 0},
    { "HalfWord Access",       dram_half_word_access, 0xFFFF,   1, 0, 0},
    { "Byte Access",           dram_byte_access,      0xFFFF,   1, 0, 0},
    { "Memory Copy",           dram_memcpy_test,      0xFFFF,   8, 0, 0},
    { "Self Address",          test_mem_self_addr,    0xFFFF,   1, 0, 0},
    { "Solid Bits",            test_mem_solid,        0xFFFF,   1, 0, 0},
    { "Alternating",           test_mem_alternating,  0xFFFF,   1, 0, 0},
    { "Random Data",           test_mem_random,       0xFFFF,  32, 0, 0},
    { "Walking Ones Left",     test_mem_leftwalk1,    0xFFFF,   1, 0, 0},
    { "Walking Ones Right",    test_mem_rightwalk1,   0xFFFF,   1, 0, 0},
    { "Walking Zeros Left",    test_mem_leftwalk0,    0xFFFF,   1, 0, 0},
    { "Walking Zeros Right",   test_mem_rightwalk0,   0xFFFF,   1, 0, 0},
    { "Random XOR",            test_mem_xor,          0xFFFF, 128, 0, 0},
    { NULL, NULL, 0, 0, 0, 0}
};

/*--------------*/
/*  pattern_tests   */
/*--------------*/
/* Run through the set of memory tests found in the 'tests[]' array. Each test needs to run
 * against each memory range. After the tests run, calculate the result statistics and print
 * them as a single message on the console. 
 */
int32_t
pattern_tests (dramMemRange *map, uint32_t map_start, uint32_t map_end, uint32_t passes)
{
    int       i, j;
    uint32_t  failures, pass, ret_err;

    failures = 0;

    for (pass = 1; pass <= passes; pass++) 
    {
        printf ("\nPass %d\n", pass);

        for (i = 0; ; i++) 
        {
            /* Did we reach the last test in the list? */
            if (!tests_pattern[i].name)
                break;

            /* Run the test over each of the allowed memory areas. */
            for (j = map_start; j < map_end; j++) 
            {
                if (!map[j].name)
                    break;
                if ( map[j].extent > 0) 
                {
                    printf ("\n%s over %s (0x%08lX..%08lX)\n",
                            tests_pattern[i].name, map[j].name, (ulong)map[j].base,
                            (ulong)map[j].base + (ulong)map[j].extent);
                    
                    ret_err = tests_pattern[i].fp (map[j].base,
                                               map[j].base + map[j].extent,
                                               tests_pattern[i].bursts);
                    
                    if (ret_err == -1) 
                    {
                        return -1;/* Interrupted by user. */
                    }
                    else
                    {
                        tests_pattern[i].failures = ret_err;
                    }
                    
                    if (tests_pattern[i].failures) 
                    {
                        printf ("Test failed: %s\n", tests_pattern[i].name);
                        tests_pattern[i].total_failures =
                            tests_pattern[i].total_failures + tests_pattern[i].failures;
                    }
                }
            }
        }
    
        /* Display the test summary information. */
        printf ("Pass %d Summary\n", pass);
        for (i = 0; ; i = i + 1) 
        {
            if (!tests_pattern[i].name)
                break;
            printf ("%30s: fail(%12u)  total_fail(%12u)\n",
                             tests_pattern[i].name,
                             tests_pattern[i].failures,
                             tests_pattern[i].total_failures);
            failures = failures + tests_pattern[i].failures;
        }
    }

    return (failures);
}


/*------------------------*/
/*  do_dram_pattern_test  */
/*------------------------*/
int do_dram_pattern_test (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    uint32_t   i, map_start, map_end, count_limit, ret_err = 0;
    int run_position = dt_probe_position();
    
    if (argc > 1)
        count_limit = (ulong)simple_strtoul(argv[1], NULL, 10);
    else
        count_limit = 10; 
    
    if(argc == 3)
        return CMD_RET_USAGE;
    
    if(argc > 3) 
    {
        map_start = MapUser;
        map_end   = MapUser + 1;
        memoryMap[MapUser].name   = "User Tester";
        memoryMap[MapUser].base   = simple_strtoul(argv[2], NULL, 16);
        memoryMap[MapUser].extent = simple_strtoul(argv[3], NULL, 16) - memoryMap[MapUser].base;
    }
    else
    {
        if((run_position == POS_IN_LOWER_BASE) || 
           (run_position == POS_IN_LOWER_RANGE))
        {
            map_start = MapUpper;
            map_end   = MapUpper + 1;
        }
        else if((run_position == POS_IN_UPPER_BASE) || 
                (run_position == POS_IN_UPPER_RANGE))
        {
            map_start = MapLower;
            map_end   = MapLower + 1;
        }
        else /* POS_IN_NULL_RANGE || POS_IN_BOTH_RANGE */
        {
            map_start = MapUser;
            map_end   = MapUser + 1;
            printf("dramtest should run in Appropriate address.\n"
                   " try to run command: reloc auto.\n\n");
            return 0;
        }
    }

    printf ("\nDram Pattern Test (built " __DATE__ "@" __TIME__ ")\n\n");
        
    puts ("Test On Memory Map: \n");
    for(i = map_start; i < map_end; i++)
    {
        if(memoryMap[i].extent > 0)
        {
            printf("%16s : 0x%08lX ~ 0x%08lX(", memoryMap[i].name,
                       (ulong)memoryMap[i].base,
                       (ulong)memoryMap[i].base + (ulong)memoryMap[i].extent);
            print_size((uint32_t)memoryMap[i].extent, ")\n");
        }
    }
    puts("\n");

    /* Run the memory tests over the  regions. */
    ret_err = pattern_tests (memoryMap, map_start, map_end, count_limit);
    if(ret_err == -1)    
        return CMD_RET_FAILURE;
        
    return (0);
}

/* Set of available Memory tests. */
testDesc tests_stable[] = {
    { "Data Bus",              run_data_bus_tests,    0xFFFF,   10, 0, 0},
    { "Address Bus",           run_addr_bus_tests,    0xFFFF,    1, 0, 0},
    { "Mtest Quick",           run_mtest_quick_tests, 0xFFFF,    1, 0, 0},
    { "Mtest Alt",             run_mtest_alt_tests,   0xFFFF,    1, 0, 0},
    { "Memory Fade",           run_mem_fade_tests,    0xFFFF,    1, 0, 0},
    { "Read-Modify-Write",     run_mem_rmw_tests,     0xFFFF,  512, 0, 0},
    { "Crosstalk",             run_dram_xtalk_tests,  0xFFFF,    1, 0, 0},
    { "Address Rot",           dram_addr_rot,         0xFFFF,    8, 0, 0},
    { "Address ~Rot",          dram_com_addr_rot,     0xFFFF,    8, 0, 0},
    { "HalfWord Access",       dram_half_word_access, 0xFFFF,    1, 0, 0},
    { "Byte Access",           dram_byte_access,      0xFFFF,    1, 0, 0},
    { "Memory Copy",           dram_memcpy_test,      0xFFFF,    8, 0, 0},
    { "Self Address",          test_mem_self_addr,    0xFFFF,    1, 0, 0},
    { "Solid Bits",            test_mem_solid,        0xFFFF,    1, 0, 0},
    { "Alternating",           test_mem_alternating,  0xFFFF,    1, 0, 0},
    { "Random Data",           test_mem_random,       0xFFFF,   32, 0, 0},
    { "Walking Ones Left",     test_mem_leftwalk1,    0xFFFF,    1, 0, 0},
    { "Walking Ones Right",    test_mem_rightwalk1,   0xFFFF,    1, 0, 0},
    { "Walking Zeros Left",    test_mem_leftwalk0,    0xFFFF,    1, 0, 0},
    { "Walking Zeros Right",   test_mem_rightwalk0,   0xFFFF,    1, 0, 0},
    { "Random XOR",            test_mem_xor,          0xFFFF,  128, 0, 0},
    { NULL, NULL, 0, 0, 0, 0}
};

/*-------------------*/
/*  stable_tests    */
/*-------------------*/
/* Run through the set of memory tests found in the 'tests[]' array. Each test needs to run
 * against each memory range. After the tests run, calculate the result statistics and print
 * them as a single message on the console. 
 */
int32_t
stable_tests (dramMemRange *map, uint32_t map_start, uint32_t map_end, uint32_t passes)
{
    int       i, j;
    uint32_t  failures, pass, ret_err;

    failures = 0;

    for (pass = 1; pass <= passes; pass++) 
    {
        printf ("\nPass %d\n", pass);

        for (i = 0; ; i++) 
        {
            /* Did we reach the last test in the list? */
            if (!tests_stable[i].name)
                break;

            /* Run the test over each of the allowed memory areas. */
            for (j = map_start; j < map_end; j++) 
            {
                if (!map[j].name)
                    break;
                if ( map[j].extent > 0) 
                {
                    printf ("\n%s over %s (0x%08lX..%08lX)\n",
                            tests_stable[i].name, map[j].name, (ulong)map[j].base,
                            (ulong)map[j].base + (ulong)map[j].extent);
                    
                    ret_err = tests_stable[i].fp (map[j].base,
                                               map[j].base + map[j].extent,
                                               tests_stable[i].bursts);
                    
                    if (ret_err == -1) 
                    {
                        return -1;/* Interrupted by user. */
                    }
                    else
                    {
                        tests_stable[i].failures = ret_err;
                    }
                    
                    if (tests_stable[i].failures) 
                    {
                        printf ("Test failed: %s\n", tests_stable[i].name);
                        tests_stable[i].total_failures =
                            tests_stable[i].total_failures + tests_stable[i].failures;
                    }
                }
            }
        }
    
        /* Display the test summary information. */
        printf ("Pass %d Summary\n", pass);
        for (i = 0; ; i = i + 1) 
        {
            if (!tests_stable[i].name)
                break;
            printf ("%30s: fail(%12u)  total_fail(%12u)\n",
                    tests_stable[i].name,
                    tests_stable[i].failures,
                    tests_stable[i].total_failures);
            failures = failures + tests_stable[i].failures;
        }
    }

    return (failures);
}

            
/*---------------------*/
/* do_dram_stable_test */
/*---------------------*/
int do_dram_stable_test (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    
    uint32_t test_type;
    uint32_t i, map_start, map_end, ret_err;
    
    int  run_position = dt_probe_position();

    if (argc > 1)
        test_type = (ulong)simple_strtoul(argv[1], NULL, 10); /* 手动运行 */
    else
        test_type = 0;  /* 自动运行，不需人工干预 */
    
    if(argc == 3)
        return CMD_RET_USAGE;
    
    if((argc > 3) && (test_type != 0)) 
    {
        map_start = MapUser;
        map_end   = MapUser + 1;
        memoryMap[MapUser].name   = "User Tester";
        memoryMap[MapUser].base   = simple_strtoul(argv[2], NULL, 16);
        memoryMap[MapUser].extent = simple_strtoul(argv[3], NULL, 16) - memoryMap[MapUser].base;
    }
    else
    {
        if((run_position == POS_IN_LOWER_BASE) || 
           (run_position == POS_IN_LOWER_RANGE))
        {
            map_start = MapUpper;
            map_end   = MapUpper + 1;
        }
        else if((run_position == POS_IN_UPPER_BASE) || 
                (run_position == POS_IN_UPPER_RANGE))
        {
            map_start = MapLower;
            map_end   = MapLower + 1;
        }
        else /* POS_IN_NULL_RANGE || POS_IN_BOTH_RANGE */
        {
            map_start = MapUser;
            map_end   = MapUser + 1;
            printf("dramtest should run in Appropriate address.\n"
                   " try to run command: reloc auto.\n\n");
            return 0;
        }
    }

    printf ("\nDram Stable Test ( built " __DATE__ "@" __TIME__ ")\n\n");
    
    puts ("Test On Memory Map: \n");
    for(i = map_start; i < map_end; i++)
    {
        if(memoryMap[i].extent > 0)
        {
            printf("%16s : 0x%08lX ~ 0x%08lX(", memoryMap[i].name,
                       (ulong)memoryMap[i].base,
                       (ulong)memoryMap[i].base + (ulong)memoryMap[i].extent);
            print_size((uint32_t)memoryMap[i].extent, ")\n");
        }
    }
	puts("\n");
        
    /* Run the memory tests over the  regions. */
    ret_err = stable_tests (memoryMap, map_start, map_end, 2);
    if(ret_err == -1)
    {
#if 0
        autoboot_enable(0);  /* disable autoboot*/
#endif
        return CMD_RET_FAILURE;
    }


    if(test_type == 0)
    {
#if 0
        autoboot_enable(1);  /* enable auto boot */
#endif
		
#ifdef CONFIG_IMAGE_COPY
        printf("\nCMD: %s\n\n", "reloc auto");
        run_command_list("reloc auto", -1, 0);
#else
		printf("dram Stable Execution in all memory range shoud define: CONFIG_IMAGE_COPY!\n");
#endif
    }
        
    return (0);
}
