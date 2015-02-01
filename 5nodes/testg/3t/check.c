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
      char firstname2[15];
      int ret;

      printf("check start\n");

      for (k = 0; k < 1000000; ++k) {
   	  sprintf(name, "username%d", k);
          sprintf(firstname, "John%d", k);
	  
	  op_id = hyperdex_client_get(client, "usertable", name, strlen(name), &op_status, &attrs, &attrs_sz);
          loop_id = hyperdex_client_loop(client, -1, &loop_status);
	  
	  //printf("gaot attribute \"%s\" = \"%.*s\"\n", attrs[0].attr, attrs[0].value_sz, attrs[0].value);
	  sprintf(firstname2, "%.*s", attrs[0].value_sz, attrs[0].value);
          //printf("got firstname2: %s\n", firstname2);
          //printf("firstname: %s\n", firstname);
	  
          ret = strncmp(firstname, firstname2);
	
	  if (ret != 0){
                printf("last from DB: %s\n", firstname2);
                printf("try get: %s\n", firstname);		 
		return 0; 
          }
      }

      printf("check done\n");

      hyperdex_client_destroy_attrs(attrs, attrs_sz);
      hyperdex_client_destroy(client);
      return EXIT_SUCCESS;
  }
