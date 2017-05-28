#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <errno.h> 
#include <fcntl.h>
#include <gmp.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <linux/random.h>

#include "random.h"

// Seed generator
static int genSeed(char *buf, size_t len);


/* 
 * === Function ===============================================================
 *         Name: genSeed
 *
 *  Description: Generates a random seed. The code for the genSeed function
 *  has been obtained from: https://cryptocoding.net/index.php/Coding_rules
 *
 *  The function generates a random number into a buffer, with the byte size
 *  of len.
 * ============================================================================
 */

static int genSeed(char *buf, size_t len){

    // The stat struct retrives information about the /dev/urandom file.
    struct stat st;

    // File descriptor for /dev/urandom.
    int fd;

    // A bitwise 'or' separated list of values that determine the method in
    // which the file is to be opened.
    int flags;

    int cnt;
    

    // Contains error values
    errno = 0; 

    // Open the file so that it is read only.
    flags = O_RDONLY;

#ifdef O_NOFOLLOW
    // If /dev/urandom is a symbolic link, then the open fails.
    flags |= O_NOFOLLOW;
#endif

#ifdef O_CLOEXEC
    // Permits a program to avoid additional F_SETFD operations
    flags |= O_CLOEXEC;
#endif

    fd = open("/dev/urandom", flags, 0);
	if (fd < 0) {
        fprintf(stderr, "[ERROR] Could not open /dev/urandom\n");
        return EXIT_FAILURE;
	}

#ifdef O_CLOEXEC
    // If the FD_CLOEXEC bit is set, /dev/urandom will automatically be closed 
    fcntl(fd, F_SETFD, fcntl(fd, F_GETFD) | FD_CLOEXEC);
#endif

    // Checks the file mode m to see whether /dev/urandom is a character device file. 
	if (fstat(fd, &st) < 0 || !S_ISCHR(st.st_mode)) {
		close(fd);
        
        fprintf(stderr, "[ERROR] %s\n", strerror(errno));
        return EXIT_FAILURE;
	}

    // Retrieve the entropy count of the input pool, the contents will
    // be the same as the entropy_avail file under proc.
    // The result will be stored in cnt.
    if (ioctl(fd, RNDGETENTCNT, &cnt) < 0) {
		close(fd);
        
        fprintf(stderr, "[ERROR] %s\n", strerror(errno));
        return EXIT_FAILURE;
    }


    size_t i;

    for (i = 0; i < len;){
		size_t wanted = len - i;

        // Read data into buffer
		ssize_t ret = read(fd, buf + i, wanted);

		if (ret < 0) {

            // Resource temporarily unavailable or 
            // Interrupted function call
			if (errno == EAGAIN || errno == EINTR)
				continue;

			
            close(fd);
            fprintf(stderr, "[ERROR] %s\n", strerror(errno));
            return EXIT_FAILURE;
		
        }
		
        i += (size_t) ret;
	}
	
    close(fd);

    return EXIT_SUCCESS;
}

/* 
 * === Function ===============================================================
 *         Name: randomUniform
 *
 *  Description: Generates a uniform random integer in the range [0, n],
 *  inclusive.
 *
 *  Takes a placeholder for the random number and the size n,
 *  that determines the range.
 * ============================================================================
 */
int randomUniform(mpz_t rand, mpz_t n){
        
    // Contains the algorithm selection and current state.
    gmp_randstate_t randState;
    
    // Buffer for the random Seed.
    char *buf;

    size_t bytes = 10;

    // Allocate memory for the seed
    buf = calloc(bytes, bytes * sizeof(char));

    // Random seed pulled from /dev/urandom
    int seed = genSeed(buf, bytes);

    if(seed){
        return EXIT_FAILURE;
    }

    // Cast the buffer to a unsigned long.
    unsigned long randomSeed = (unsigned long) buf;

    // The mpz_urandomm generates a uniform random number [0, n-1]
    // so to obtain [0, n] we add one to the n.
    mpz_add_ui(n, n, 1);

    // Init randState for a Mersenne Twister algorithm.
    gmp_randinit_mt(randState);
    
    // Set an initial seed value into randState.
    gmp_randseed_ui(randState, randomSeed);

    // Generates the random integer.
    mpz_urandomm(rand, randState, n);

    // Free allocated memory for randState.
    gmp_randclear(randState);

    // Free buffer.
    free(buf);

    return EXIT_SUCCESS;
}

