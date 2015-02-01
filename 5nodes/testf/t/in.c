  #include <hyperdex/client.h>
  int
  main(int argc, const char* argv[])
  {
      struct hyperdex_client* client = NULL;
      struct hyperdex_client_attribute attr;
      struct hyperdex_client_attribute* attrs;
      size_t attrs_sz = 0;
      int64_t op_id;
      enum hyperdex_client_returncode op_status;
      int64_t loop_id;
      enum hyperdex_client_returncode loop_status;
      size_t i;
      size_t k;
      client = hyperdex_client_create("192.168.100.1", 1982);
      char name[15];
      char firstname[15];

      for (k = 0; k < 1000000; ++k) {
   	  sprintf(name, "username%d", k);
          attr.attr = "field0";
          sprintf(firstname, "John%d", k);
          attr.value = firstname;
          attr.value_sz = strlen(attr.value);
          attr.datatype = HYPERDATATYPE_STRING;

          op_id = hyperdex_client_put(client, "usertable", name, strlen(name), &attr, 1, &op_status);
          loop_id = hyperdex_client_loop(client, -1, &loop_status);

          op_id = hyperdex_client_get(client, "usertable", name, strlen(name), &op_status, &attrs, &attrs_sz);
          loop_id = hyperdex_client_loop(client, -1, &loop_status);
          printf("put \"%s\" get done\n", name);

          //for (i = 0; i < attrs_sz; ++i) {
          //    printf("got attribute \"%s\" = \"%.*s\"\n", attrs[i].attr, attrs[i].value_sz, attrs[i].value);
          //}
        }

      hyperdex_client_destroy_attrs(attrs, attrs_sz);
      hyperdex_client_destroy(client);
      return EXIT_SUCCESS;
  }
