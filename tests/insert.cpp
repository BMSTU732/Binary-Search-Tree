#include "catch.hpp"
#include <BinarySearchTree.hpp>
SCENARIO ("Insert item when object already exists")
{
    GIVEN ("object")
    {
        BinarySearchTree <int> tree={1,2};
        int object=5;
        WHEN ("insert")
        {
            tree.insert(object);
            THEN ("if it in the tree")
            {
                REQUIRE(!tree.insert(object));
            }
        };

    }
}
SCENARIO ("Insert item when object doesn't exist")
{
    GIVEN ("object")
    {
        BinarySearchTree <int> tree={1,2};
        int object=5;
        WHEN ("insert")
        {
            THEN ("if it is not in the tree")
            {
                REQUIRE(tree.insert(object));
            }
        };

    }
}
SCENARIO ("If object < root")
{
    GIVEN ("object and root")
    {
        BinarySearchTree <int> tree={5,2};
        int object=1;
        BinarySearchTree <int> rez={5,2,1};

        WHEN ("insert")
        {
            tree.insert(object);
            THEN ("put it on the left") 
            { 
                REQUIRE(tree==rez);
            }
        };
    }
}
SCENARIO ("If object > root")
{
    GIVEN ("object and root")
    {
        BinarySearchTree <int> tree={1,2};
        int object=3;
        BinarySearchTree <int> rez={1,2,3};

        WHEN ("insert")
        {
            tree.insert(object);
            THEN ("put it on the right") {REQUIRE(tree==rez);}
        };
    }
}
SCENARIO ("If object already exists")
{
    GIVEN ("object")
    {
        BinarySearchTree <int> tree={1,2};
        int object=2;
        auto currsize=tree.size();
        WHEN ("insert")
        {
            tree.insert(object);
            THEN ("if it in the tree")
            {
                REQUIRE(tree.size()==currsize);
            }
        };

    }
}
SCENARIO ("If object doesn't exist")
{
    GIVEN ("object")
    {
        BinarySearchTree <int> tree={1,2};
        int object=5;
        auto currsize=tree.size();
        WHEN ("insert")
        {
            tree.insert(object);
            THEN ("if it is not in the tree")
            {
                REQUIRE(tree.size()==currsize+1);
            }
        };

    }
}
