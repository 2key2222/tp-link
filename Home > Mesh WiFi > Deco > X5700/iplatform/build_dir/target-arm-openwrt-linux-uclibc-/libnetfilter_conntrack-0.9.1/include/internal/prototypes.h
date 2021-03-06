#ifndef _NFCT_PROTOTYPES_H_
#define _NFCT_PROTOTYPES_H_

/*
 * conntrack internal prototypes
 */
int __build_conntrack(struct nfnl_subsys_handle *ssh, struct nfnlhdr *req, size_t size, u_int16_t type, u_int16_t flags, const struct nf_conntrack *ct);
void __build_tuple(struct nfnlhdr *req, size_t size, const struct __nfct_tuple *t, const int type);
int __parse_message_type(const struct nlmsghdr *nlh);
void __parse_conntrack(const struct nlmsghdr *nlh, struct nfattr *cda[], struct nf_conntrack *ct);
void __parse_tuple(const struct nfattr *attr, struct __nfct_tuple *tuple, int dir, u_int32_t *set);
int __snprintf_conntrack(char *buf, unsigned int len, const struct nf_conntrack *ct, unsigned int type, unsigned int msg_output, unsigned int flags);
int __snprintf_address(char *buf, unsigned int len, const struct __nfct_tuple *tuple);
int __snprintf_protocol(char *buf, unsigned int len, const struct nf_conntrack *ct);
int __snprintf_proto(char *buf, unsigned int len, const struct __nfct_tuple *tuple);
int __snprintf_conntrack_default(char *buf, unsigned int len, const struct nf_conntrack *ct, const unsigned int msg_type, const unsigned int flags);
int __snprintf_conntrack_xml(char *buf, unsigned int len, const struct nf_conntrack *ct, const unsigned int msg_type, const unsigned int flags);

int __callback(struct nlmsghdr *nlh, struct nfattr *nfa[], void *data);

int __setobjopt(struct nf_conntrack *ct, unsigned int option);
int __getobjopt(const struct nf_conntrack *ct, unsigned int option);
int __compare(const struct nf_conntrack *ct1, const struct nf_conntrack *ct2, unsigned int flags);
void __copy_fast(struct nf_conntrack *ct1, const struct nf_conntrack *ct);

int __setup_netlink_socket_filter(int fd, struct nfct_filter *filter);

/*
 * expectation internal prototypes
 */
int __build_expect(struct nfnl_subsys_handle *ssh, struct nfnlhdr *req, size_t size, u_int16_t type, u_int16_t flags, const struct nf_expect *exp);
int __parse_expect_message_type(const struct nlmsghdr *nlh);
void __parse_expect(const struct nlmsghdr *nlh, struct nfattr *cda[], struct nf_expect *exp);
int __expect_callback(struct nlmsghdr *nlh, struct nfattr *nfa[], void *data);
int __snprintf_expect(char *buf, unsigned int len, const struct nf_expect *exp, unsigned int type, unsigned int msg_output, unsigned int flags);
int __snprintf_expect_default(char *buf, unsigned int len, const struct nf_expect *exp, unsigned int msg_type, unsigned int flags);

#endif
