// TestFood.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>



static void exit_nicely(PGconn *conn)
{
	PQfinish(conn);
	exit(1);
}


int main(int argc, char** argv)
{
	const char *conninfo;
	PGconn     *conn;
	PGresult   *res;
	int         nFields;
	int         i,
		j;

	/*
	* If the user supplies a parameter on the command line, use it as the
	* conninfo string; otherwise default to setting dbname=postgres and using
	* environment variables or defaults for all other connection parameters.
	*/
	if (argc > 1)
		conninfo = argv[1];
	else
		conninfo = "dbname = postgres";

	/* Make a connection to the database */
	conn = PQconnectdb(conninfo);

	/* Check to see that the backend connection was successfully made */
	if (PQstatus(conn) != CONNECTION_OK)
	{
		fprintf(stderr, "Connection to database failed: %s",
			PQerrorMessage(conn));
		exit_nicely(conn);
	}

	




	/* close the portal ... we don't bother to check for errors ... */
	res = PQexec(conn, "CLOSE myportal");
	PQclear(res);

	/* end the transaction */
	res = PQexec(conn, "END");
	PQclear(res);

	/* close the connection to the database and cleanup */
	PQfinish(conn);

	return 0;
}

