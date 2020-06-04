/*....................................THIS PROGRAM GENERATES A PRIME NUMBER OF GIVEN NUMBER OF BIT USING GMP LIBRARY................................*/

#include<stdio.h>
#include<gmp.h>
#include<time.h>

void prime_gen();
int miller_rabin_gmp(mpz_t);                                                                 /*returns 0 if n is prime*/
void square_and_mult_modulo_gmp(mpz_t,mpz_t,mpz_t);

mpz_t prime_key,p,b_univ;
int key_len,no_of_tests;
gmp_randstate_t state;

time_t start_mycode,end_mycode,start_gmp,end_gmp;
int row,col,duration_mycode,duration_gmp,data_mycode[50][50],data_gmp[50][50];

int main()
{

mpz_init(prime_key);
int test,i,j,k;
gmp_randinit_mt(state);
mpz_init(p);

printf("time analysis table mycode/gmp");

for(row=1;row<=5;row++)
{

key_len=row*200;

printf("\nbit-length %d: ",key_len);

for(col=1;col<=5;col++)
{

no_of_tests=col*20;

duration_mycode=0;
duration_gmp=0;


prime_gen();
mpz_set(p,prime_key);

time(&start_gmp);                // logging of time starts
test=mpz_probab_prime_p(prime_key,no_of_tests);
time(&end_gmp);                  // logging of time ends

duration_mycode=end_mycode-start_mycode;
duration_gmp=end_gmp-start_gmp;

data_mycode[row][col]=duration_mycode;
data_gmp[row][col]=duration_gmp;

printf("  %d/%d",data_mycode[row][col],data_gmp[row][col]);

}

}

mpz_clear(p);

printf("\n");

return 0;

}


void prime_gen()
{

int flag=1,i,n_is_composite;
mpz_t k;
mpz_init(k);

while(flag)
{
mpz_urandomb(prime_key,state,key_len);

mpz_ui_pow_ui(k,2,key_len-1);
if(mpz_cmp(prime_key,k)>0)

{

time(&start_mycode);                         //  logging of time starts

for(i=1;i<=no_of_tests;i++)
{

n_is_composite=miller_rabin_gmp(prime_key);

if(n_is_composite==1)
break;

}

time(&end_mycode);                           //    logging of time ends

if(n_is_composite==0)
flag=0;

}

}

mpz_clear(k);

}


int miller_rabin_gmp(mpz_t n)
{

int k=0,flag=1,i,c=0;
unsigned long int junk;
mpz_t m,a,b,b_mod_n,n_1;

mpz_init(m);
mpz_init(a);
mpz_init(b);
mpz_init(b_mod_n);
mpz_init(n_1);
mpz_init(b_univ);

mpz_sub_ui (m,n,1);
mpz_sub_ui (n_1,n,1);

while(mpz_even_p(m))
{
k++;
junk=mpz_fdiv_q_ui(m,m,2);
}

while(flag)
{
mpz_urandomb(a,state,key_len-3);

if(mpz_cmp(n,a)>0)
flag=0;

}

square_and_mult_modulo_gmp(a,m,n);
mpz_set(b,b_univ);

mpz_mod(b_mod_n,b,n);
if(mpz_cmp_si(b_mod_n,1)==0)
return 0;                                                                                     /*returns 0 if n is prime*/

for(i=0;i<=k-1;i++)
{

mpz_mod(b_mod_n,b,n);
if(mpz_cmp(b_mod_n,n_1)==0)
return 0;                                                                                    /*returns 0 if n is prime*/

else
{
mpz_mul(b,b,b);
mpz_mod(b,b,n);
}

}

mpz_clear(m);
mpz_clear(a);
mpz_clear(b);
mpz_clear(b_mod_n);
mpz_clear(n_1);

return 1;                                                                                    /*returns 1 if composite*/

}


/*generates parameter1 to the power parameter2 modulo parameter3 using square multiply method*/

void square_and_mult_modulo_gmp(mpz_t x,mpz_t c,mpz_t n)
{

mpz_t z,c_copy;
int c_bin[3000],i=0,l=0;
unsigned long int junk;

mpz_init(z);
mpz_init(c_copy);

mpz_add_ui (z,z,1);
mpz_set(c_copy,c);

while(mpz_cmp_ui(c_copy,0)!=0)
{

c_bin[i]=mpz_odd_p(c_copy);
junk=mpz_fdiv_q_ui(c_copy,c_copy,2);

i++;
l++;

}

for(i=l-1;i>=0;i--)
{

mpz_mul(z,z,z);
mpz_mod(z,z,n);

if(c_bin[i]!=0)
mpz_mul(z,z,x);
mpz_mod(z,z,n);

}

mpz_set(b_univ,z);
mpz_clear(c_copy);

}

