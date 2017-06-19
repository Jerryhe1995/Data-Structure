#ifndef __kdtree__
#define __kdtree__
#include <string>

class KDNode {
    private:
        double latitude;
        double longitude;
        std::string description;
        KDNode *left;
        KDNode *right;
        // perhaps you want to include `depth` as well

        // this function returs the distance in miles from lat, lon
        // to this object
        double distance(double lat, double lon);

    public:
        KDNode(double lat, double lot, const char *desc);
        ~KDNode();

    friend class KDTree;
};

class KDTree {
    private:
        unsigned int size;
        int count;
        KDNode *root;

        void destroy(KDNode **p);
		void insert(KDNode **p, double lat, double lon, int depth, const char *desc);
		double mtodegreelat( double radius);
        double mtodegreelon( double latitude ,double radius);
		void preorder(KDNode *p);
		void printNeighbors(KDNode **p, double lat, double lon, double rad, int depth, const char *filter, int *count);

    public:
        KDTree();
        ~KDTree();

        unsigned int getSize();
        void insert(double lat, double lon, const char *desc);
        unsigned int printNeighbors(double lat, double lon, double rad, const char *filter);
		void print_all();
};

#endif