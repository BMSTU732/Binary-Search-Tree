#include "../include/BinarySearchTree.h"
#include "catch.hpp"

#include "catch.hpp"
#include <BinarySearchTree.hpp>
SCENARIO ("Size of empty tree must be 0", "[size 0]")
{
    GIVEN ("tree is empty")
    {
        BinarySearchTree <int> tree;
                        WHEN ("decide size")
                        {
                            THEN ("size must be 0")
                            {
                                REQUIRE(tree.size()==0);
                            }
                        };

    }
}
SCENARIO ("Size of not empty tree is not 0!", "[size !0]")
{
    GIVEN("tree is not empty")
    {
        BinarySearchTree <int> tree = {1};
        WHEN("decide size")
         {
             THEN ("size is not 0")
             {
              REQUIRE(tree.size()!=0)   ;
             }
         }
    }
}
SCENARIO("Size for const & !const ", "[const&!const]")
{
  GIVEN("const & non-const object")
  {
      BinarySearchTree<int> t1={1,2,3};
      const BinarySearchTree<int> t2={2,3,4};
      WHEN ("decide size")
      {
       THEN ("sizes must be equal")
       {
           REQUIRE(t1.size()==t2.size());
       }
      }
  }
}
