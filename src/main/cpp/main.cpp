#include <iostream>
#include <gmp.h>
#include <gmpxx.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <assert.h>
#include <semaphore.h> 
#include <random>
#include <string>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>


using namespace std;


int isSGPrime(mpz_class n){
	int res = mpz_probab_prime_p(n.get_mpz_t(), 10);
	if(!res)
		return 0;
	mpz_class safe_prime = (n<<1) + 1;
	if(mpz_probab_prime_p(safe_prime.get_mpz_t(), 10))
		return min(
				mpz_probab_prime_p(n.get_mpz_t(), 50),
				mpz_probab_prime_p(safe_prime.get_mpz_t(), 50)
			  );
	return 0;
}

int main(int argc, char**argv){


	struct timeval time; 

	gettimeofday(&time,NULL);

	srand((time.tv_sec * 1000) + (time.tv_usec / 1000));


    mpz_class increment = 1;

    for(mpz_class i = 2; i < 300; ++i)
        if(mpz_probab_prime_p(i.get_mpz_t(), 50))
            increment *= i;


	string str("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
	random_device rd;
	mt19937 generator(rd());
	shuffle(str.begin(), str.end(), generator);


	sem_t *sem = sem_open(str.c_str(), O_CREAT, 0644, 1);

	int count = atoi(argv[1])-1;
	int procs = atoi(argv[2])-1;
	assert(procs>0);
	while(procs-- && fork())
		usleep(1123456 + rand()%2123456);

	gettimeofday(&time,NULL);

	srand((time.tv_sec * 1000) + (time.tv_usec / 1000));

	mpz_class n, offset=0;
	n = 1;  //some prime
	for(int i = 1; i < count; ++i)
	{
		n *= 2;
		if(i > 30 && i + 2 < count && rand()%2)
			offset += n;
	}
	if(n>1)
		n += 1;
	n += offset;
    mpz_class tmp_inc = 2;
	while(true){
		n += tmp_inc;
		if(isSGPrime(n))
		{
			sem_wait(sem);
			cout<<2*n+1<<endl;
			sem_post(sem);
            tmp_inc = increment;
		}
	}


}
