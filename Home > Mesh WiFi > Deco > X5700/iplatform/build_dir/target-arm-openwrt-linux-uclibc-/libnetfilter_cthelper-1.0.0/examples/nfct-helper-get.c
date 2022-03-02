/* This example is in the public domain. */
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <libmnl/libmnl.h>
#include <libnetfilter_cthelper/libnetfilter_cthelper.h>

static int nfct_helper_cb(const struct nlmsghdr *nlh, void *data)
{
	struct nfct_helper *nfct_helper;
	char buf[4096];

	nfct_helper = nfct_helper_alloc();
	if (nfct_helper == NULL) {
		perror("OOM");
		goto err;
	}

	if (nfct_helper_nlmsg_parse_payload(nlh, nfct_helper) < 0) {
		perror("nfct_helper_parse_nl_msg");
		goto err_free;
	}

	nfct_helper_snprintf(buf, sizeof(buf), nfct_helper, 0, 0);
	printf("%s\n", buf);

err_free:
	nfct_helper_free(nfct_helper);
err:
	return MNL_CB_OK;
}

int main(int argc, char *argv[])
{
	struct mnl_socket *nl;
	char buf[MNL_SOCKET_BUFFER_SIZE];
	struct nlmsghdr *nlh;
	uint32_t portid, seq;
	int ret, full = 1;

	if (argc != 1) {
		fprintf(stderr, "Usage: %s\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	seq = time(NULL);
	nlh = nfct_helper_nlmsg_build_hdr(buf, NFNL_MSG_CTHELPER_GET,
					NLM_F_DUMP, seq);

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
		ret = mnl_cb_run(buf, ret, seq, portid, nfct_helper_cb, &full);
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
