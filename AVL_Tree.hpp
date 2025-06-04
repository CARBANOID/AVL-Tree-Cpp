#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include<iostream>
#include<cmath>
#include<queue>
using namespace std ;


class Node{
	public : 
	int data ;
	int height ; 
	Node *Left ; 
	Node *Right ;
	
	Node(int data){
	    this->data = data ; 
	    height = 1 ; 
	    Left = Right = NULL ;
	}
	
	inline bool IsBalanced(){
	    int Lh = 0 , Rh = 0 ; 
	    if(this->Right) Rh = this->Right->height ; 
	    if(this->Left) Lh = this->Left->height ; 
	    return (abs(Lh - Rh) <= 1) ;
	}
};



class AVL{
	public : 
	Node *root = NULL ; 
	
	
	void get_AVL_height(){
		 cout << "Height of AVL Tree : "  ;
		 (root) ? cout <<  root->height : cout << 0 ;
		 cout << endl << endl ;	
	}
	
	void setheight(Node *curr){
		int hr = 0 , hl = 0 ;
		if(curr->Right) hr = curr->Right->height  ;
		if(curr->Left) hl = curr->Left->height  ;
		curr->height = 1 + max(hr,hl) ;		
	}	
	
	
	void IsAVL(){
		if(IsAVL(root)) cout << "Tree is AVL Tree" << endl ;
		else cout << "Tree is not a AVL Tree" ;
	}
	
	bool IsAVL(Node *curr){
		if(curr == NULL) return true ;
		if(!IsAVL(curr->Left) || !IsAVL(curr->Right)) return false ;
		return curr->IsBalanced() ;
	}
	
//	Insertion

	void InsertKeys(vector<int>Keys){
		for(auto k : Keys) this->Insert(k) ;
	}

	void Insert(int val){
		cout << "Inserting Value : " << val << endl ;	// FOR DEBUGGING
		root = Insert(root,val) ;
		levelorder() ;	// FOR DEBUGGING
		cout << endl <<endl << endl << endl ;
		return ;
	}
	
	Node* Insert(Node*curr,int &val){
		if(curr == NULL){
			curr = new Node(val) ; 
			cout << "Inserted" << endl ; // FOR DEBUGGING
			return curr ; 
		}
		else if(val > curr->data) curr->Right = Insert(curr->Right,val) ; 
		else curr->Left = Insert(curr->Left,val) ; 
		
		if(!curr->IsBalanced()){
			
//			FOR DEBUGGING -> start
			int Lh = 0 , Rh = 0 ; 
			if(curr->Right) Rh = curr->Right->height ; 
			if(curr->Left) Lh = curr->Left->height ; 
			
			cout << "Faulty Node : " << curr->data << "	 LeftSubtree Height : " << Lh << "   RightSubtree Height : " << Rh << endl ;
//			FOR DEBUGGING -> end
			
			curr = Rotate(curr) ;
			return curr ; 
		}
	 	setheight(curr) ; 
	 	return curr ;
	}
	
	
	
//----------------------------------------------------------------------------------------------------------------------
   // Deletion	

	void DeleteKeys(vector<int>Keys){
		for(auto k : Keys) this->Delete(k) ;
	}

	void Delete(int val){
		cout << "Deleting Value : " << val << endl ;	// FOR DEBUGGING
		root = Delete(root,val) ;
		if(root) levelorder() ;	// FOR DEBUGGING
		cout << endl <<endl << endl << endl ;
		return ;
	}
	
	Node *Successor(Node *curr,Node* real){
		if(curr->Left){
		  curr->Left = Successor(curr->Left,real) ;

		  if(!curr->IsBalanced()) {
			int Lh = 0 , Rh = 0 ; 
			if(curr->Right) Rh = curr->Right->height ; 
			if(curr->Left) Lh = curr->Left->height ; 
			
			cout << "Faulty Node : " << curr->data << "	 LeftSubtree Height : " << Lh << "   RightSubtree Height : " << Rh << endl ;

		  	curr = Rotate(curr) ;
		  	return curr ;
		  }
		  setheight(curr) ; 
			
		  return curr ; 
		}
		else {
			swap(real->data,curr->data) ;
			if(curr->Right){
				Node *temp = curr->Right ; 
				delete curr ; 
				cout << "Deleted" << endl ;
				return temp ; 
			}
			else{
				delete curr ; 
				cout << "Deleted" << endl ;
				return NULL ;
			}
		}
	}
	
	
	Node* Delete(Node *curr,int &val){

		if(curr == NULL){
			cout <<  "Node Not Present" << endl  ;
			return NULL ; 
		}
		if(val == curr->data){
			if(curr->Left && curr->Right){
				curr->Right = Successor(curr->Right,curr) ;
			}
			else if(curr->Left){
				Node *temp = curr->Left ; 
				delete curr ; 
				cout << "Deleted" << endl ;
				return temp ; 
			}
			else if(curr->Right){
				Node *temp = curr->Right ; 
				delete curr ; 
				cout << "Deleted" << endl ;
				return temp ; 
			}
			else{
				delete curr ; 
				cout << "Deleted" << endl ;
				return NULL ;	
			}
		}else if(val > curr->data) curr->Right = Delete(curr->Right,val) ;
		else curr->Left = Delete(curr->Left,val) ;
		if(!curr->IsBalanced()){
			int Lh = 0 , Rh = 0 ; 
			if(curr->Right) Rh = curr->Right->height ; 
			if(curr->Left) Lh = curr->Left->height ; 
			
			cout << "Faulty Node : " << curr->data << "	 LeftSubtree Height : " << Lh << "   RightSubtree Height : " << Rh << endl ;
				
			curr = Rotate(curr) ;
			return curr ;
		}
		setheight(curr) ; 
		return curr ; 
	}
	

// ------------------------------------------------------------------------------------------------------------------
//	Rotation Functions
	
	Node* Rotate(Node *curr){	
		cout << "Rotation Type : " ;	// For Debugging	
		int lh = (curr->Left) ? curr->Left->height : 0 ;
		int rh = (curr->Right) ? curr->Right->height : 0 ;
		
		if(lh > rh){
			int llh = (curr->Left->Left) ? curr->Left->Left->height : 0 ;
			if(lh == llh + 1){
				cout << "LL" << endl ;	// For Debugging	
				curr = LL(curr) ;
				setheight(curr) ;
			}
			else { // lh == lrh +1 
				cout << "LR" << endl ;	// For Debugging	
				curr = LR(curr) ;
			}
		}
		else{
			int rrh = (curr->Right->Right) ? curr->Right->Right->height : 0 ;
			if(rh == rrh + 1){
				cout << "RR" << endl ;	// For Debugging	
				curr = RR(curr) ;
				setheight(curr) ;
			}
			else { // rh == rlh +1 
				cout << "RL" << endl ;	// For Debugging	
				curr = RL(curr) ;
			}
		}
		return curr ;
	}	
	
	Node* LL(Node *curr){
		Node *Lcurr = curr->Left ; 
		Node *LLcurr = Lcurr->Left ; 
		curr->Left = Lcurr->Right ; 
		Lcurr->Right = curr ; 
		setheight(curr) ; 
		return Lcurr ; 
	}

	Node* RR(Node *curr){
		Node *Rcurr = curr->Right ; 
		Node *RRcurr = Rcurr->Right ; 
		curr->Right = Rcurr->Left ; 
		Rcurr->Left = curr ;
		setheight(curr) ; 
		return Rcurr ;
	}	
	
	Node* RL(Node *curr){
		Node *Rcurr = curr->Right ; 
		Node *RLcurr = Rcurr->Left ; 
		curr->Right = RLcurr ; 
		Rcurr->Left = RLcurr->Right ; 
		RLcurr->Right = Rcurr ; 
		cout << "1st Rotation" << endl ;	// For Debugging	
		levelorder() ;	// FOR DEBUGGING
		cout << endl ;
		cout << "2nd Rotation" << endl ;	// For Debugging	
		setheight(Rcurr) ; 
		setheight(RLcurr) ; 
		return RR(curr) ; 
	}
	
	Node* LR(Node *curr){
		Node *Lcurr = curr->Left ; 
		Node *LRcurr = Lcurr->Right ; 
		curr->Left = LRcurr ; 
		Lcurr->Right = LRcurr->Left ; 
		LRcurr->Left = Lcurr ; 
		cout << "1st Rotation" << endl ;	// For Debugging	
		levelorder() ;	// FOR DEBUGGING
		cout << endl ;
		cout << "2nd Rotation" << endl ; 	// For Debugging	
		setheight(Lcurr) ; 
		setheight(LRcurr) ; 
		return LL(curr) ; 
	}
	
	
	
//-------------------------------------------------------------------------------------------------------------------
	
// Functions For Debugging

	Node *newline = NULL ;	
	void levelorder(){				
		queue<Node*>q ; 	
		q.push(root) ; 	
		q.push(newline) ;
		
		while(!q.empty()){
			Node *front = q.front() ; 
			q.pop() ;
			
			if(front == NULL){
				if(!q.empty()){
					cout << endl ;
					q.push(front) ; 
				}
				else break ;
			}
			else{
				cout << front->data << " " ; ;
				if(front->Left) q.push(front->Left) ; 
				if(front->Right) q.push(front->Right) ;
			}
		}
	}
	
	void inorder(){
		inorder(root) ;
 	}
	inline void inorder(Node *curr){
		if(curr == NULL) return ;
		inorder(curr->Left) ; 
		cout << curr->data << " " ; 
		inorder(curr->Right) ; 
	}
//---------------------------------------------------------------------------------------------------------------------	
};

#endif // AVL_TREE_HPP 
