#include "Main.hpp"

int main()
{
    #ifdef performance
        struct timeval start, end;
        long long elapsed;

        QTree* tree;
        std::map<long long, long long>* map;

        QTree* tree_clone;
        std::map<long long, long long>* map_clone;

        /* insert qtree */
        tree = qtr_create();

        printf("Running Performance tests on tree operations with 10 Million Nodes:\n");

        gettimeofday(&start, NULL);
        for(long long l = 0;l < 10000000; l++)
        {
            qtr_set(tree, l, (void*)l);
        }
        gettimeofday(&end, NULL);

        elapsed = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
        printf(" *QTree insert: %lld ms\n", elapsed/1000);

        /* insert Red Black Tree */
        map = new std::map<long long, long long>();

        gettimeofday(&start, NULL);
        for(long long l = 0;l < 10000000; l++)
        {
            map->insert(std::pair<long long, long long>(l,l));
        }
        gettimeofday(&end, NULL);

        elapsed = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
        printf(" *Red Black Tree insert: %lld ms\n", elapsed/1000);

        /* search qtree */
        gettimeofday(&start, NULL);
        for(long long l = 0;l < 10000000; l++)
        {
            qtr_get(tree, l);
        }
        gettimeofday(&end, NULL);

        elapsed = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
        printf(" *QTree search: %lld ms\n", elapsed/1000);

        /* search Red Black Tree */
        gettimeofday(&start, NULL);
        for(long long l = 0;l < 10000000; l++)
        {
            map->at(l);
        }
        gettimeofday(&end, NULL);

        elapsed = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
        printf(" *Red Black Tree search: %lld ms\n", elapsed/1000);

        /* clone qtree */
        gettimeofday(&start, NULL);
        tree_clone = qtr_clone(tree);
        gettimeofday(&end, NULL);

        elapsed = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
        printf(" *QTree clone: %lld ms\n", elapsed/1000);

        /* clone Red Black Tree */
        gettimeofday(&start, NULL);
        map_clone = new std::map<long long, long long>(*map);
        gettimeofday(&end, NULL);

        elapsed = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
        printf(" *Red Black Tree clone: %lld ms\n", elapsed/1000);

        /* delete qtree */
        gettimeofday(&start, NULL);
        for(long long l = 0;l < 10000000; l++)
        {
            qtr_delete(tree, l);
        }
        gettimeofday(&end, NULL);

        elapsed = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
        printf(" *QTree delete: %lld ms\n", elapsed/1000);

        /* remove qtree */
        gettimeofday(&start, NULL);
        for(long long l = 0;l < 10000000; l++)
        {
            qtr_remove(tree_clone, l);
        }
        gettimeofday(&end, NULL);

        elapsed = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
        printf(" *QTree remove: %lld ms\n", elapsed/1000);


        /* delete Red Black Tree */
        gettimeofday(&start, NULL);
        for(long long l = 0;l < 10000000; l++)
        {
            map->erase(l);
        }
        gettimeofday(&end, NULL);

        elapsed = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
        printf(" *Red Black Tree delete: %lld ms\n", elapsed/1000);
        printf("Done.\n");
        return 0;
    #elif defined(preview)
        QTree* tree = qtr_create();
    
        qtr_set(tree, 8, (void*)2);
        qtr_set(tree, 18, (void*)7);
        qtr_set(tree, 5, (void*)9);
        qtr_set(tree, 15, (void*)64);
        qtr_set(tree, 17, (void*)4);
        qtr_set(tree, 25, (void*)67);
        qtr_set(tree, 40, (void*)11);
        qtr_set(tree, 80, (void*)175);
        qtr_set(tree, 33, (void*)45);

        printf("Values:\n");
        printf(" -%lld\n", qtr_get(tree, 8));
        printf(" -%lld\n", qtr_get(tree, 18));
        printf(" -%lld\n", qtr_get(tree, 5));
        printf(" -%lld\n", qtr_get(tree, 15));
        printf(" -%lld\n", qtr_get(tree, 17));
        printf(" -%lld\n", qtr_get(tree, 25));
        printf(" -%lld\n", qtr_get(tree, 40));
        printf(" -%lld\n", qtr_get(tree, 80));
        printf(" -%lld\n", qtr_get(tree, 33));

        printf("Tree:\n");
        qtr_print(tree);

        /* remove would have the same effect, but wouldn't change the tree structure */
        qtr_delete(tree, 17);

        printf("Values after deleting node with key 17:\n");
        printf(" -%lld\n", qtr_get(tree, 8));
        printf(" -%lld\n", qtr_get(tree, 18));
        printf(" -%lld\n", qtr_get(tree, 5));
        printf(" -%lld\n", qtr_get(tree, 15));
        printf(" -%lld\n", qtr_get(tree, 17));
        printf(" -%lld\n", qtr_get(tree, 25));
        printf(" -%lld\n", qtr_get(tree, 40));
        printf(" -%lld\n", qtr_get(tree, 80));
        printf(" -%lld\n", qtr_get(tree, 33));
        printf("Tree after deleting node with key 17:\n");
        qtr_print(tree);
        return 0;
    #else
        printf("./qtree.sh preview - shows you the tree structure\n");
        printf("./qtree.sh performance - compares the Red Black Tree and the QTree Algorithm using tests\n");
        return 0;
    #endif
}