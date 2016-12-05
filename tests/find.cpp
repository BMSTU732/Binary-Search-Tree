#include "catch.hpp"
#include <BinarySearchTree.hpp>

SCENARIO ("Find item when object exists")
{
    GIVEN ("object")
    {
        BinarySearchTree <int> tree={1,2,3,4,5,6};
        int object=5;
        WHEN ("find it")
        {
            tree.find(object);
            THEN ("if it exists")
            {
                REQUIRE(tree.find(object)!= nullptr );
            }
        };

    }
}
SCENARIO ("Find item when object doesn't exist")
{

    GIVEN("object")
    {
        BinarySearchTree <int> tree={1,2,3,4,5,6};
        int object=100;
            WHEN ("find it") {
                tree.find(object);
                THEN ("if doesn't exist")
                {
                    REQUIRE(tree.find(object)==nullptr);
                }
            }
    }
}

SCENARIO ("If const or non-const")
{
    GIVEN("object")
    {
        BinarySearchTree <int> t1={1,2,3,4,5};
        const BinarySearchTree <int> t2={1,2,3,4,5,6};
        
        WHEN ("it exists") {
            int object=5;
            THEN ("result must do not be nullptr")
            {
                REQUIRE(t1.find(object)!=nullptr);
                REQUIRE(t2.find(object)!= nullptr);
            }
        }
        WHEN ("it do not exists") {
            int object=7;
            THEN ("result must be nullptr")
            {
                REQUIRE(t1.find(object)==nullptr);
                REQUIRE(t2.find(object)==nullptr);
            }
        }
    }
}
