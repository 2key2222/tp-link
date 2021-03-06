#include <stdio.h>
#include <inttypes.h>

#include "blobmsg.h"
#include "blobmsg_json.h"

static const char *indent_str = "\t\t\t\t\t\t\t\t\t\t\t\t\t";

#define indent_printf(indent, ...) do { \
	if (indent > 0) \
		fwrite(indent_str, indent, 1, stderr); \
	fprintf(stderr, __VA_ARGS__); \
} while(0)

static void dump_attr_data(struct blob_attr *data, int indent, int next_indent);

static void
dump_table(struct blob_attr *head, int len, int indent, bool array)
{
	struct blob_attr *attr;
	struct blobmsg_hdr *hdr;

	indent_printf(indent, "{\n");
	__blob_for_each_attr(attr, head, len) {
		hdr = blob_data(attr);
		if (!array)
			indent_printf(indent + 1, "%s : ", hdr->name);
		dump_attr_data(attr, 0, indent + 1);
	}
	indent_printf(indent, "}\n");
}

static void dump_attr_data(struct blob_attr *data, int indent, int next_indent)
{
	int type = blobmsg_type(data);
	switch(type) {
	case BLOBMSG_TYPE_STRING:
		indent_printf(indent, "%s\n", blobmsg_get_string(data));
		break;
	case BLOBMSG_TYPE_INT8:
		indent_printf(indent, "%d\n", blobmsg_get_u8(data));
		break;
	case BLOBMSG_TYPE_INT16:
		indent_printf(indent, "%d\n", blobmsg_get_u16(data));
		break;
	case BLOBMSG_TYPE_INT32:
		indent_printf(indent, "%d\n", blobmsg_get_u32(data));
		break;
	case BLOBMSG_TYPE_INT64:
		indent_printf(indent, "%"PRIu64"\n", blobmsg_get_u64(data));
		break;
    case BLOBMSG_TYPE_DOUBLE:
		indent_printf(indent, "%lf\n", blobmsg_get_double(data));
		break;
	case BLOBMSG_TYPE_TABLE:
	case BLOBMSG_TYPE_ARRAY:
		if (!indent)
			indent_printf(indent, "\n");
		dump_table(blobmsg_data(data), blobmsg_data_len(data),
			   next_indent, type == BLOBMSG_TYPE_ARRAY);
		break;
	}
}

enum {
	FOO_MESSAGE,
	FOO_LIST,
	FOO_TESTDATA
};

static const struct blobmsg_policy pol[] = {
	[FOO_MESSAGE] = {
		.name = "message",
		.type = BLOBMSG_TYPE_STRING,
	},
	[FOO_LIST] = {
		.name = "list",
		.type = BLOBMSG_TYPE_ARRAY,
	},
	[FOO_TESTDATA] = {
		.name = "testdata",
		.type = BLOBMSG_TYPE_TABLE,
	},
};

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#endif

static void dump_message(struct blob_buf *buf)
{
	struct blob_attr *tb[ARRAY_SIZE(pol)];

	if (blobmsg_parse(pol, ARRAY_SIZE(pol), tb, blob_data(buf->head), blob_len(buf->head)) != 0) {
		fprintf(stderr, "Parse failed\n");
		return;
	}
	if (tb[FOO_MESSAGE])
		fprintf(stderr, "Message: %s\n", (char *) blobmsg_data(tb[FOO_MESSAGE]));

	if (tb[FOO_LIST]) {
		fprintf(stderr, "List: ");
		dump_table(blobmsg_data(tb[FOO_LIST]), blobmsg_data_len(tb[FOO_LIST]), 0, true);
	}
	if (tb[FOO_TESTDATA]) {
		fprintf(stderr, "Testdata: ");
		dump_table(blobmsg_data(tb[FOO_TESTDATA]), blobmsg_data_len(tb[FOO_TESTDATA]), 0, false);
	}
}

static void
fill_message(struct blob_buf *buf)
{
	void *tbl;

	blobmsg_add_string(buf, "message", "Hello, world!");

	tbl = blobmsg_open_table(buf, "testdata");
	blobmsg_add_u32(buf, "hello", 1);
	blobmsg_add_string(buf, "world", "2");
	blobmsg_close_table(buf, tbl);

	tbl = blobmsg_open_array(buf, "list");
	blobmsg_add_u32(buf, NULL, 0);
	blobmsg_add_u32(buf, NULL, 1);
	blobmsg_add_u32(buf, NULL, 2);
	blobmsg_close_table(buf, tbl);
}

int main(int argc, char **argv)
{
	static struct blob_buf buf;

	blobmsg_buf_init(&buf);
	fill_message(&buf);
	dump_message(&buf);
	fprintf(stderr, "json: %s\n", blobmsg_format_json(buf.head, true));

	if (buf.buf)
		free(buf.buf);

	return 0;
}
