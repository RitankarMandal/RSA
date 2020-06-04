# RSA
This project is built using The GNU Multiple Precision Arithmetic Library. 
See https://gmplib.org/ for information about how to install this library in your machine. 

rsa_gmp.c generates public and private keys. 
enc_gmp.c encrypts the plain text to cipher text. 
dec_gmp.c decrypts the cipher text to plain text. 
attack.c implements Weiner's low bit attack. See https://en.wikipedia.org/wiki/Wiener%27s_attack. 
