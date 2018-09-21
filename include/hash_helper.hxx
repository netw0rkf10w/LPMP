#ifndef LPMP_HASH_HELPER_HXX
#define LPMP_HASH_HELPER_HXX

namespace LPMP {
   // hash function for various types
   namespace hash {
      // equivalent of boost hash combine
      inline size_t hash_combine( size_t lhs, size_t rhs ) {
         lhs^= rhs + 0x9e3779b9 + (lhs << 6) + (lhs >> 2);
         return lhs;
      }

      template<typename T, size_t N>
      size_t hash_array(const std::array<T,N>& x)
      {
         size_t hash = std::hash<T>()(x[0]);
         for(std::size_t i=0; i<N; ++i) {
            hash = hash_combine(hash, std::hash<T>()(x[i]));
         }
         return hash; 
      }
   }
} // namespace LPMP

// insert hash functions from above into standard namespace
namespace std
{
    template<size_t N> struct hash<std::array<std::size_t,N>>
    {
        typedef std::array<std::size_t,N> argument_type;
        typedef std::size_t result_type;
        result_type operator()(argument_type const& s) const
        {
            return LPMP::hash::hash_array(s);
        }
    };
}

#endif // LPMP_HASH_HELPER_HXX