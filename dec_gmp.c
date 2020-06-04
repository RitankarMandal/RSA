                                /*................................RSA decrypter system................................*/

#include<stdio.h>
#include<gmp.h>

mpz_t plain_text,cipher_text,a_pri_key,n_p_mul_q;
char ch_ci_txt[500],ch_a_txt[500],ch_n_txt[500];

void square_and_mult_modulo_gmp(mpz_t,mpz_t,mpz_t);


int main()
{

int j;

printf("RSA decrypter system\nEnter your cipher text here to decrypt\n");
scanf("%s",ch_ci_txt);

printf("Enter your private decyption key a_pri__key :  ");
scanf("%s",ch_a_txt);

printf("Enter your private decyption key n_p_mult_q :  ");
scanf("%s",ch_n_txt);

j=mpz_init_set_str(cipher_text,ch_ci_txt,0);
j=mpz_init_set_str(a_pri_key,ch_a_txt,0);
j=mpz_init_set_str(n_p_mul_q,ch_n_txt,0);

square_and_mult_modulo_gmp(cipher_text,a_pri_key,n_p_mul_q);

gmp_printf("plain text is :  %Zd\n",plain_text);

return 0;

}


/*generates parameter1 to the power parameter2 modulo parameter3 using square multiply method*/

void square_and_mult_modulo_gmp(mpz_t x,mpz_t c,mpz_t n)
{

mpz_t z,c_copy;
int c_bin[5000],i=0,l=0;
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
mpz_set(plain_text,z);
mpz_clear(c_copy);

}


