#include "KDTree.h"
#include <math.h>
#include <iostream>

KDNode::KDNode(double lat, double lon, const char *desc) {
    left = NULL;
    right = NULL;
    description = desc;
    latitude = lat;
    longitude = lon;
}

KDNode::~KDNode() {
}

double KDNode::distance(double lat, double lon) {
    double param = M_PI / 180.0; // required for conversion from degrees to radians
    double rad = 3956.0;  // radius of earth in miles
    double d_lat = (lat - latitude) * param;
    double d_lon = (lon - longitude) * param;
    double dist = sin(d_lat/2) * sin(d_lat/2) + cos(latitude*param) * cos(lat*param) * sin(d_lon/2) * sin(d_lon/2);
    dist = 2.0 * atan2(sqrt(dist), sqrt(1-dist));
    return rad * dist;
}
/*convert mile into latitude
*/
double KDTree::mtodegreelat( double radius){
    double param = M_PI / 180.0; // required for conversion from degrees to radians
    double earthrad = 3956.0;  // radius of earth in miles
	double rad=radius/earthrad;
    return rad /param;	
}
/*convert mile into longitude
*/
double KDTree::mtodegreelon( double latitude ,double radius){
	double param = M_PI / 180.0; // required for conversion from degrees to radians
    double earthrad = 3956.0;  // radius of earth in miles
	double rad= radius / abs(  (earthrad*cos(latitude*param)  )  );// 
    return rad /param;
}

KDTree::KDTree() {
    root = NULL;
    size = 0;
}

KDTree::~KDTree() {
    destroy(&root);
}

void KDTree::destroy(KDNode **p) {
    if (*p){
   //postorder traverse
	destroy(&(*p)->left);
	destroy(&(*p)->right);
	delete *p;
	}
}


void KDTree::insert(double lat, double lon, const char *desc) {
    insert(&root, lat, lon, 0, desc);
	//seeds recursive function with the root,the depth is equal to 0;
}

/*if depth is even, we need to check x coordinates, and y if odd
*/
void KDTree::insert(KDNode **p, double lat, double lon, int depth, const char *desc) {
    // new node if there is no node here already
	if (!*p){
		(*p) = new KDNode(lat,lon,desc);
		size++;
	}	
	else{
		// if depth is even, we need to check x coordinates, and y if odd
		if (depth % 2 == 0){
			// checking x values
			// x coordinates are longitude
			if((*p)->longitude < lon){
				depth++;
				insert(&((*p)->right), lat, lon, depth, desc);
			}
			else if((*p)->longitude >= lon){
				depth++;
				insert(&((*p)->left), lat, lon, depth, desc);
			}
		}
		else{
			// checking y values
			// y coordinates are latitude
			if((*p)->latitude < lat){
				depth++;
				insert(&((*p)->right), lat, lon, depth, desc);
			}
			else if((*p)->latitude >= lat){
				depth++;
				insert(&((*p)->left), lat, lon, depth, desc);
			}
		}		
	}	
}	

unsigned int KDTree::printNeighbors(double lat, double lon, double rad, const char *filter) {
    // TODO
	//count = 0;
	int count =0;
	//seeds recursive function with the root
	printNeighbors(&root, lat, lon, rad, 0, filter,&count);
	return count;
}

/*use distance function to print the node in the circle with radius and center point;
  we convert radius into degree, and check the node is inside the x y limit, 
           if within the circle limits, go both side 
		   els go towards the circle
 preorder traversal with filter
*/
void KDTree::printNeighbors(KDNode **p, double lat, double lon, double rad, int depth, const char *filter,int *count){
	// base case of no node
	if ((*p)==NULL){
		return;
	}	
	//if the filter is satisfied then increment coount
	if ( (*p)->distance(lat, lon) < rad && (*p)->description.find(filter) != std::string::npos){
		(*count)++;
		std::cout << (*p)->longitude << " , " << (*p)->latitude <<" : "<<(*p)->description << std::endl;
	}
	// if depth is even, we need to check x coordinates and y if odd
	if (depth % 2 == 0){
		// checking x values
		// x coordinates are longitude
		//within the x limits
		
		double longRad =  mtodegreelon(lat, rad);
	   if(  (  (  lon - mtodegreelon(lat, rad)  ) <= (*p)->longitude ) &&    (*p)->longitude <= (lon + mtodegreelon(lat, rad) ) ){
			depth++;
			printNeighbors(&((*p)->right), lat, lon, rad, depth, filter,count);
			printNeighbors(&((*p)->left), lat, lon, rad, depth, filter,count);
		}				
		// on the left hand of the x limits
		else if((*p)->longitude < (lon-mtodegreelon(lat, rad) ) ){
			depth++;
			printNeighbors(&((*p)->right), lat, lon, rad, depth, filter,count);
		}
		//on the right hand of the x limits
		else {  
			depth++;
			printNeighbors(&((*p)->left), lat, lon, rad, depth, filter,count);
		}
	}
	//check y values
	else{  
		double latRad = mtodegreelat(rad);
		//within the y limits
		if( lat - mtodegreelat( rad) < (*p)->latitude  && (*p)->latitude < lat + mtodegreelat( rad)){
			depth++;
			printNeighbors(&((*p)->right), lat, lon, rad, depth, filter,count);
			printNeighbors(&((*p)->left), lat, lon, rad, depth, filter,count);
		}
		// on the left hand of the y limits
		else if( (*p)->latitude <= lat - mtodegreelat( rad) ){
			depth++;
			printNeighbors(&((*p)->right), lat, lon, rad, depth, filter,count);
		}
		//on the right hand of the x limits
		else{
			depth++;
			printNeighbors(&((*p)->left), lat, lon, rad, depth, filter,count);
		}
	}	
}


unsigned int KDTree::getSize() {
    return size;
	//size is incremented by the insert function, reflects the number of nodes in the tree.
}

// prints all nodes for tests
void KDTree::print_all(){
	preorder(root);	
}
// same, preorder traversal helper function of print_all;
void KDTree::preorder(KDNode *p){
	if (p){
		std::cout << p->longitude << " , " << p->latitude <<" : "<<p->description << " " << p->distance(2.5,2.5) << std::endl;
		preorder(p->left);
		preorder(p->right);
	}
}

