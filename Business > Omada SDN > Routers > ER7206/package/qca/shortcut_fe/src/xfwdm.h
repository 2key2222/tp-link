#ifndef __XFWDM_H__
#define __XFWDM_H__


#ifdef __cplusplus
extern "C"
{
#endif  /* __cplusplus */

#define NETLINK_XFWDM    	(26)
#define XFWDM_ARGV_LEN 		(128)

typedef enum xfwdm_op_type {
	XFWDM_OP_TYPE_FLUSH = 0,
	XFWDM_OP_TYPE_CLEAN = 1,
	XFWDM_OP_TYPE_MAX
} XFWDM_OP_TYPE;

typedef enum xfwdm_op_obj_type {
	XFWDM_OP_OBJ_ALL = 0,
	XFWDM_OP_OBJ_IP,
	XFWDM_OP_OBJ_SRC_IP,
	XFWDM_OP_OBJ_DST_IP,
	XFWDM_OP_OBJ_MAC,
	XFWDM_OP_OBJ_SRC_MAC,
	XFWDM_OP_OBJ_DST_MAC,
	XFWDM_OP_OBJ_IF,
	XFWDM_OP_OBJ_SRC_IF,
	XFWDM_OP_OBJ_DST_IF,
	XFWDM_OP_OBJ_MAX
} XFWDM_OPT_OBJ_TYPE;

typedef struct xfwdm_opt {
	int op_type;
	int op_obj;
	char op_argv[XFWDM_ARGV_LEN];
	int print;
} XFWDM_OPT;

#ifdef __cplusplus
}
#endif  /* __cplusplus */


#endif  /* __XFWDM_H__ */
