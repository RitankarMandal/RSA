               /*....................................THIS PROGRAM GENERATES RSA KEYS FOR ENCRYPTION................................*/

#include<stdio.h>
#include<gmp.h>

void prime_gen();
int miller_rabin_gmp(mpz_t);                                                                 /*returns 0 if n is prime*/
void square_and_mult_modulo_gmp(mpz_t,mpz_t,mpz_t);
void gcd_gmp(mpz_t,mpz_t,mpz_t);
void inverse_gmp(mpz_t,mpz_t,mpz_t);

mpz_t prime_key,p,q,n_p_mul_q,phi_n,p_1,q_1,b_univ,b_pub_key,a_pri_key,res;
int key_len,key_len_2;
gmp_randstate_t state;

int main()
{

mpz_init(prime_key);
int test,flag=1;
gmp_randinit_mt(state);
mpz_init(p);
mpz_init(q);
mpz_init(n_p_mul_q);
mpz_init(phi_n);
mpz_init(p_1);
mpz_init(q_1);
mpz_init(b_pub_key);
mpz_init(a_pri_key);
mpz_init(res);
mpz_t l;
mpz_init(l);


printf("Enter the bit length of the first prime number:  ");
scanf("%d",&key_len);

prime_gen();
mpz_set(p,prime_key);
gmp_printf ("The first prime number of given bit is :  %Zd\n",p);

test=mpz_probab_prime_p(prime_key,10);
if(test==0) printf("\ngmp says it is composite\n");
else printf("gmp says it is prime\n");

printf("Enter the bit length of the second prime number:  ");
scanf("%d",&key_len);

prime_gen();
mpz_set(q,prime_key);
gmp_printf ("The second prime number of given bit is :  %Zd\n",q);

test=mpz_probab_prime_p(prime_key,10);
if(test==0) printf("\ngmp says it is composite\n");
else printf("gmp says it is prime\n");

mpz_mul(n_p_mul_q,p,q);
mpz_sub_ui (p_1,p,1);
mpz_sub_ui (q_1,q,1);
mpz_mul(phi_n,p_1,q_1);

gmp_printf ("n_p_mul_q : %Zd\n",n_p_mul_q);
gmp_printf ("phi_n : %Zd\n",phi_n);

printf("Enter the bit length of the b_public_key:  ");
scanf("%d",&key_len_2);

while(flag)
{

mpz_urandomb(b_pub_key,state,key_len_2);

mpz_ui_pow_ui(l,2,key_len_2-1);

if(mpz_cmp(b_pub_key,l)>0)

{

gcd_gmp(res,b_pub_key,phi_n);                                                             /*put the gcd of b and phi_n to res*/

if(mpz_cmp_ui(res,1)==0)
flag=0;

}

}

inverse_gmp(a_pri_key,b_pub_key,phi_n);

gmp_printf("b_pub_key :  %Zd\na_pri_key :  %Zd\n",b_pub_key,a_pri_key);


mpz_clear(p);
mpz_clear(q);
mpz_clear(n_p_mul_q);
mpz_clear(p_1);
mpz_clear(q_1);
mpz_clear(phi_n);
mpz_clear(b_pub_key);
mpz_clear(a_pri_key);
mpz_clear(res);
mpz_clear(l);

return 0;

}


void prime_gen()
{

int i,flag=1,n_is_composite=1;
mpz_t k;
mpz_init(k);

while(flag)
{
mpz_urandomb(prime_key,state,key_len);

mpz_ui_pow_ui(k,2,key_len-1);

if(mpz_cmp(prime_key,k)>0)

{

for(i=1;i<=10;i++)
{

n_is_composite=miller_rabin_gmp(prime_key);

if(n_is_composite==1)
break;

}

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
int c_bin[1000],i=0,l=0;
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



void gcd_gmp(mpz_t res,mpz_t b_pub_key,mpz_t phi_n)
{

mpz_t b_gcd,p_gcd,r_gcd;

mpz_init(b_gcd);
mpz_init(p_gcd);
mpz_init(r_gcd);

mpz_set(b_gcd,b_pub_key);
mpz_set(p_gcd,phi_n);

mpz_mod(r_gcd,p_gcd,b_gcd);


while(mpz_cmp_ui(r_gcd,0)!=0)
{

mpz_set(p_gcd,b_gcd);
mpz_set(b_gcd,r_gcd);

mpz_mod(r_gcd,p_gcd,b_gcd);

}

mpz_set(res,b_gcd);

mpz_clear(b_gcd);
mpz_clear(p_gcd);
mpz_clear(r_gcd);

}



void inverse_gmp(mpz_t a_pri_key,mpz_t b_pub_key,mpz_t phi_n)
{

mpz_t a0,b0,t0,t1,q_in,r_in,temp,j;

mpz_init(a0);
mpz_init(b0);
mpz_init(t0);
mpz_init(t1);
mpz_init(q_in);
mpz_init(r_in);
mpz_init(temp);
mpz_init(j);

mpz_set(a0,phi_n);
mpz_set(b0,b_pub_key);
mpz_set_ui(t0,0);
mpz_set_ui(t1,1);
mpz_fdiv_qr(q_in,r_in,a0,b0);

while(mpz_sgn(r_in)==1)
{

mpz_mul(j,q_in,t1);
mpz_sub(j,t0,j);
mpz_mod(temp,j,phi_n);

mpz_set(t0,t1);
mpz_set(t1,temp);
mpz_set(a0,b0);
mpz_set(b0,r_in);
mpz_fdiv_qr(q_in,r_in,a0,b0);

}

mpz_set(a_pri_key,t1);

mpz_clear(a0);
mpz_clear(b0);mpz_clear(t0);
mpz_clear(t1);
mpz_clear(q_in);
mpz_clear(r_in);
mpz_clear(temp);
mpz_clear(j);


}
