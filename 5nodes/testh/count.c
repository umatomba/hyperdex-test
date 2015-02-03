  #include <hyperdex/client.h>
  #include <time.h>
  int
  main(int argc, const char* argv[])
  {
      struct hyperdex_client* client = NULL;
      struct hyperdex_client_attribute attr;
      struct hyperdex_client_attribute* attrs;
      size_t attrs_sz = 0;
      int64_t op_id = 0;
      enum hyperdex_client_returncode op_status;
      int64_t loop_id;
      enum hyperdex_client_returncode loop_status;
      size_t i;
      size_t k;
      client = hyperdex_client_create("192.168.100.1", 1982);
      char name[15];
      char firstname[15];
      
      struct hyperdex_client_attribute_check check;
      enum hyperdex_client_returncode count_status;
      uint64_t ct_sz = 0;
      //check.attr = "username";
      check.attr = "k";
      check.value = ".*";
      check.value_sz = strlen(check.value);
      check.datatype = HYPERDATATYPE_STRING;
      check.predicate =  HYPERPREDICATE_REGEX;

      //op_id = hyperdex_client_count(client, "phonebook", &check, 1, &count_status, &ct_sz);
      op_id = hyperdex_client_count(client, "usertable", &check, 1, &count_status, &ct_sz);

      loop_id = hyperdex_client_loop(client, 30, &loop_status);
      printf("count = %d | op_id: %d | count_status:%d\n", ct_sz, op_id, count_status);
     
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
