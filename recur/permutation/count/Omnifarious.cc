#include <iostream> 
#include <stdexcept> 
#include <string>
 
uint64_t fact(unsigned int v) 
{ 
   uint64_t output = 1; 
   for (unsigned int i = 2; i <= v; ++i) { 
      output *= i; 
   } 
   return output; 
} 
 
void permute(const ::std::string &s) 
{ 
   using ::std::cout; 
   typedef ::std::string::size_type size_t; 
 
   static unsigned int max_size = 20;  // 21! > 2^64 
 
   const size_t strsize = s.size(); 
 
   if (strsize > max_size) { 
      throw ::std::overflow_error("This function can only permute strings of size 20 or less."); 
   } else if (strsize < 1) { 
      return; 
   } else if (strsize == 1) { 
      cout << "0 : " << s << '\n'; 
   } else { 
      const uint64_t num_perms = fact(s.size()); 
      // Go through each permutation one-by-one 
      for (uint64_t perm = 0; perm < num_perms; ++perm) { 
         // The indexes of the original characters in the new permutation 
         size_t idxs[max_size]; 
 
         // The indexes of the original characters in the new permutation in 
         // terms of the list remaining after the first n characters are pulled 
         // out. 
         size_t residuals[max_size]; 
 
         // We use div to pull our permutation number apart into a set of 
         // indexes.  This holds what's left of the permutation number. 
         uint64_t permleft = perm; 
 
         // For a given permutation figure out which character from the original 
         // goes in each slot in the new permutation.  We start assuming that 
         // any character could go in any slot, then narrow it down to the 
         // remaining characters with each step. 
         for (unsigned int i = strsize; i > 0; permleft /= i, --i) { 
            uint64_t taken_char = permleft % i; 
            residuals[strsize - i] = taken_char; 
 
            // Translate indexes in terms of the list of remaining characters 
            // into indexes in terms of the original string. 
            for (unsigned int o = (strsize - i); o > 0; --o) { 
               if (taken_char >= residuals[o - 1]) { 
                  ++taken_char; 
               } 
            } 
            idxs[strsize - i] = taken_char; 
         } 
         cout << perm << " : "; 
         for (unsigned int i = 0; i < strsize; ++i) { 
            cout << s[idxs[i]]; 
         } 
         cout << '\n'; 
      } 
   } 
} 

int main()
{
	std::string str;
	std::cin >> str;
    permute(str);
    return 0;
}
