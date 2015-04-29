#define _POSIX_C_SOURCE 199900L

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

/*
 * Receives isensors data on the standard input and emits equivalent
 * Miffles channel data on the standard output.
 */

#define NANO_TO_MILLI(x)  ((x)/((long)1000000))

#define CCSDS_APP_PROC_NAME_LEN 32
#define MF_CHAN_NAME_LEN 128
#define MF_CHAN_DATA_COUNT 8
#define MF_CHAN_DATA_LEN 128
#define MF_CHAN_TIME_LEN 25

typedef struct _mf_chan_rec {
	char app_proc_name[ CCSDS_APP_PROC_NAME_LEN ];
	struct timespec datetime;
	char chan_name[ MF_CHAN_NAME_LEN ];
	char chan_data[ MF_CHAN_DATA_COUNT ][ MF_CHAN_DATA_LEN ];
} mf_chan_rec_t;

#define mf_chan_rec_init(r) (void)memset((r),0,sizeof(mf_chan_rec_t))

#define mf_chan_set_app_proc_name(r,s) \
	strncpy((r)->app_proc_name,(s),CCSDS_APP_PROC_NAME_LEN)
#define mf_chan_set_name(r,s) \
	strncpy((r)->chan_name,(s),MF_CHAN_NAME_LEN)
#define mf_chan_set_val_str(r,i,s) \
	strncpy((r)->chan_data[(i)],(s),MF_CHAN_DATA_LEN)


char *conv_miffles_timespec_to_str( struct timespec *ts, char *buf )
{
	static const char *month_names[ 12 ] = {
		"Jan", "Feb", "Mar", "Apr", "May", "Jun",
		"Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
	};
	
	struct tm tm;

	if ( ! ts ) return NULL;
	if ( ! buf ) return NULL;

	gmtime_r( &ts->tv_sec, &tm );

	sprintf( buf, "%04d-%3s-%02d-%02d:%02d:%02d.%03ld",
			 tm.tm_year + 1900,
			 month_names[ tm.tm_mon ],
			 tm.tm_mday,
			 tm.tm_hour,
			 tm.tm_min,
			 tm.tm_sec,
			 NANO_TO_MILLI( ts->tv_nsec ) );
	
	return buf;
}


int conv_miffles_emit( FILE *f, mf_chan_rec_t *r )
{
	char ts[ MF_CHAN_TIME_LEN ];
	if ( ! f ) return -1;
	if ( ! r ) return -1;

	fprintf( f, "%-12s %s %16s",
			 r->app_proc_name,
			 conv_miffles_timespec_to_str( &r->datetime, ts ),
			 r->chan_name );
	for ( int i = 0; i < MF_CHAN_DATA_COUNT; ++i ) {
		fprintf( f, " %s",
				 r->chan_data[i][0] ? r->chan_data[i] : "-" );
	}
	fprintf( f, "\n" );
	return 0;
}


int conv_split( const char delim, char *args[], const int argmax, char *buf )
{
	for ( int i = 0; i < argmax; ++i ) args[ i ] = NULL;
	int argc = 0;
	char *p = buf;
	while ( 1 ) {
		if ( *p == 0 ) break;
		if ( *p == '\n' ) {
			*p = 0; break;
		}
		if ( args[ argc ] == NULL ) args[ argc ] = p;
		if ( *p == delim ) {
			++argc;
			*p = 0;
		}
		++p;
	}
	
	return argc;
}

typedef struct _conv_context {
	struct timespec conv_epoch;
	struct timespec sensor_epoch;
} conv_context_t;

#define conv_context_init(c) (void)memset((c),0,sizeof(conv_context_t))

#define NANOS_IN_WHOLE 1000000000L

void timespec_add( timespec *result, timespec *left, timespec *right )
{
}

void timespec_sub( timespec *result, timespec *left, timespec *right )
{
}

#define timespec_copy(r,t) (r).tv_sec=(t).tv_sec,(r).tv_nsec=(t).tv_nsec


void timespec_set( timespec *r, double d)
{
	r->tv_sec = (long) d;
	r->tv_nsec = (long) ( ( d - r->.tv_sec ) * NANOS_IN_WHOLE );
}
	
#define ISENSOR_ACCEL "ACCEL"
#define ISENSOR_COMPASS "COMPASS"
#define ISENSOR_GPS "GPS"
#define ISENSOR_GYRO "GYRO"

int conv_isensor_to_miffles_chan( conv_context_t *c,
								  char *buf,
								  mf_chan_rec_t r[],
								  int n )
{
	static const int argmax = 16;
	char *args[ argmax ];
	int n_recs = 0;
	int i=0;
	timespec sensor_time;

	if ( ! c ) return -1;
	if ( ! buf ) return -1;
	if ( ! r ) return -1;

	int argc = conv_split( ',', args, argmax, buf );
	if ( argc <= 0 ) return -1;

	timespec_set( &sensor_time, atof( args[ 1 ] ) );

	if ( ! strcmp( args[ 0 ], ISENSOR_ACCEL ) ) {
		mf_chan_set_app_proc_name( &r[i], "IMU" );	
		if ( ( c->conv_epoch.tv_sec == 0 ) &&
			 ( c->sensor_epoch.tv_sec == 0 ) ) {
			clock_gettime( CLOCK_REALTIME, &c->conv_epoch );
			timespec_copy( c->sensor_epoch, sensor_time );
		}
		timespec elapsed;
		long elapsed_isecs = sensor_isecs - c->sensor_epoch.tv_sec;
		long elapsed_nsecs = sensor_nsecs - c->sensor_epoch.tv_nsec;
		if ( elapsed_nsecs < 0 ) {
			elapsed_nsecs += 1000000000L;
			elapsed_isecs--;
		}
		r[i].datetime.tv_sec = c->conv_epoch.tv_sec + elapsed_isecs;
		r[i].datetime.tv_nsec = c->conv_epoch.tv_nsec + elapsed_nsecs;
		if ( r[i].datetime.tv_nsec > 1000000000L ) {
			r[i].datetime.tv_nsec -= 1000000000L;
			r[i].datetime.tv_sec++;
		}
		mf_chan_set_name( &r[i], "accel" );
		mf_chan_set_val_str( &r[i], 0, args[ 2 ] );
		mf_chan_set_val_str( &r[i], 1, args[ 3 ] );
		mf_chan_set_val_str( &r[i], 2, args[ 4 ] );
		++i;
	} else if ( ! strcmp( args[ 0 ], ISENSOR_COMPASS ) ) {
	} else if ( ! strcmp( args[ 0 ], ISENSOR_GPS ) ) {
	} else if ( ! strcmp( args[ 0 ], ISENSOR_GYRO ) ) {
	}

	return i;
}
				 

#define BUFLEN 1024
int conv_isensor_translate( FILE *fin, FILE *fout )
{
	char buf[ BUFLEN ];
	static const int n_recs = 5;
	mf_chan_rec_t recs[ n_recs ];
	conv_context_t ctxt;

	conv_context_init( &ctxt );
	while ( fgets( buf, BUFLEN, fin ) != NULL ) {
		int rc = 0;
		for ( int i = 0; i < n_recs; ++i ) {
			mf_chan_rec_init( &recs[ i ] );
		}
		rc = conv_isensor_to_miffles_chan( &ctxt, buf, recs, n_recs );
		for ( int i = 0; i < rc; ++i ) {
			(void) conv_miffles_emit( fout, &recs[ i ] );
		}
	}
	return 0;
}


int main( int argc, char *argv[] )
{
	(void) conv_isensor_translate( stdin, stdout );
	return 0;
}
