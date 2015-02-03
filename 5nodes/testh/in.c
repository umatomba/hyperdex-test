  #include <hyperdex/client.h>
  #include <time.h>
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

          str();

          op_id = hyperdex_client_put(client, "usertable", name, strlen(name), &attr, 1, &op_status);
          loop_id = hyperdex_client_loop(client, 30, &loop_status);
	  printf("put \"%s\" return status: %d, ", name, op_status);
	  while (op_status != 8448) {
		printf("bdrtrn\n");
		op_id = hyperdex_client_put(client, "usertable", name, strlen(name), &attr, 1, &op_status);
		loop_id = hyperdex_client_loop(client, 30, &loop_status);
		printf("retry return status: %d\n", op_status);
	  }

	  stp();

          op_id = hyperdex_client_get(client, "usertable", name, strlen(name), &op_status, &attrs, &attrs_sz);
          loop_id = hyperdex_client_loop(client, 30, &loop_status);
          printf("get \"%s\" done\n", name);
        }

      hyperdex_client_destroy_attrs(attrs, attrs_sz);
      hyperdex_client_destroy(client);
      return EXIT_SUCCESS;
  }

struct timespec tstart={0,0}, tend={0,0};

inline void str()
{
	clock_gettime(CLOCK_MONOTONIC, &tstart);
}

inline void stp()
{
	clock_gettime(CLOCK_MONOTONIC, &tend);
	printf("done in %.5f seconds\n",
           ((double)tend.tv_sec + 1.0e-9*tend.tv_nsec) -
           ((double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec));

}
