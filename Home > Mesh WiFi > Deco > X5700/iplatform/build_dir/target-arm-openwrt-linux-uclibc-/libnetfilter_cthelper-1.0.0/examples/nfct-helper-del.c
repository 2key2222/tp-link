/* This example is in the public domain. */
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <libmnl/libmnl.h>
#include <libnetfilter_cthelper/libnetfilter_cthelper.h>

int main(int argc, char *argv[])
{
	struct mnl_socket *nl;
	char buf[MNL_SOCKET_BUFFER_SIZE];
	struct nlmsghdr *nlh;
	uint32_t portid, seq;
	struct nfct_helper *nfct_helper;
	int ret;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s [name]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	nfct_helper = nfct_helper_alloc();
	if (nfct_helper == NULL) {
		perror("OOM");
		exit(EXIT_FAILURE);
	}

	nfct_helper_attr_set(nfct_helper, NFCTH_ATTR_NAME, argv[1]);

	seq = time(NULL);
	nlh = nfct_helper_nlmsg_build_hdr(buf, NFNL_MSG_CTHELPER_DEL,
				     NLM_F_ACK, seq);
	nfct_helper_nlmsg_build_payload(nlh, nfct_helper);

	nfct_helper_free(nfct_helper);

	nl = mnl_socket_open(NETLINK_NETFILTER);
	if (nl == NULL) {
		perror("mnl_socket_open");
		exit(EXIT_FAILURE);
	}

	if (mnl_socket_bind(nl, 0, MNL_SOCKET_AUTOPID) < 0) {
		perror("mnl_socket_bind");
		exit(EXIT_FAILURE);
	}
	portid = mnl_socket_get_portid(nl);

	if (mnl_socket_sendto(nl, nlh, nlh->nlmsg_len) < 0) {
		perror("mnl_socket_send");
		exit(EXIT_FAILURE);
	}

	ret = mnl_socket_recvfrom(nl, buf, sizeof(buf));
	while (ret > 0) {
		ret = mnl_cb_run(buf, ret, seq, portid, NULL, NULL);
		if (ret <= 0)
			break;
		ret = mnl_socket_recvfrom(nl, buf, sizeof(buf));
	}
	if (ret == -1) {
		perror("error");
		exit(EXIT_FAILURE);
	}
	mnl_socket_close(nl);

	return EXIT_SUCCESS;
}
