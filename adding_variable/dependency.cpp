#include "rose.h"
#include "dependency.h"
//#include "gcd_banerjee.hpp"
#include "ds.hpp"
//#include "readWrie.h"
#include <iostream>
#include <set>
#include <vector>
#include <iterator>

#include <algorithm>
using namespace std;
using namespace SageInterface;
using namespace SageBuilder;




/*class visitorTraversal : public AstSimpleProcessing
{
    public:
       virtual void visit(SgNode* n);
};*/
static int i=0;

/*vector<string> instersection_read(vector<string> &v1, vector<string> &v2,vector<string> &read,vector<string> &write,vector<string> &v)
{

    vector<string> v3;

    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());
    sort(read.begin(), read.end());
     sort(write.begin(),write.end());
     vector<string>::iterator is,ie,i1s,i1e,readitr,writeitr,output;
     is=v1.begin();
     ie=v1.end();
     i1s=v2.begin();
     i1e=v2.end();
     output=v.begin();
     readitr=read.begin();
     writeitr=write.begin();
   while(is!=ie && i1s!=i1e)
   {
     if(*is<*i1s)
     {
       ++is;
       readitr++; 


     }
     else
     {
       if(!(*i1s<*is))
       {
           v.push_back(*readitr);
        //   cout<<"value"<<*readitr<<"\n";
           readitr++;
           is++;
       }
       i1s++;
       writeitr++;
     }
   }
   return v;
}
*/
void display(loop* head)
{
  loop* temp1=head;
   if(head==NULL)
    return;
           while(temp1)
           {
              cout<<"loop number = "<<temp1->loop_number<<"\n";
               dep_data* temp2=temp1->dep;
                    while(temp2)
                    {
                        cout<<"statement number = "<<temp2->statement_no<<"\n";
                         vector<SgNode*>::iterator i;
                           for (i=temp2->write_ref.begin(); i!=temp2->write_ref.end(); ++i)
                              std::cout <<" write ref =" << (*i)->unparseToString()<<"\n";
                            for (i=temp2->read_ref.begin(); i!=temp2->read_ref.end(); ++i)
                              std::cout <<" read_ref =" << (*i)->unparseToString()<<"\n";
                            
                         temp2=temp2->next;
                   }
                temp1=temp1->next;
           }
}
void calculate_node(loop* node)
{
  int i=0;
  while(node)
  {
    i++;
    node=node->next;
  }
  cout<<"i= "<<i<<"\n";
}
void calculate_intersection_RAW(loop* node)
{   
    
       
      vector<SgNode*>::iterator i;
    
    
     loop* temp=node;
     while(temp)
      {
       
        loop* node1=new loop;
        node1->next=NULL;
        node1->dep=NULL;
        if(intersect_RAW==NULL)
        {
           
        intersect_RAW=node1;
        }
        else
        { //cout<<" creating new node "<<"\n";
           loop* temp1=intersect_RAW;
        while(temp1->next)
          {
            temp1=temp1->next;
          }
        temp1->next=node1;
        }
       
           node1->loop_number=temp->loop_number;
          dep_data* a=temp->dep;

           while(a)
           {
             int j=0;
              dep_data* b=a;
              while(b)
              {
              for(i=b->read_ref.begin();i!=b->read_ref.end();i++)
              {   
                 
                  string a1=a->write_ref[0]->unparseToString();
                  string b1=(*i)->unparseToString();
                //  cout<<"a1 = "<<a1 <<"\n";
                 //  cout<<"b1 = "<<b1 <<"\n";
                 if(a1[0]==b1[0])
                 {
                 //  cout<<" in "<<"\n";
                  dep_data* dep1=new dep_data;
                  dep1->next=NULL;
                  dep1->statement_no=a->statement_no;
                  dep_data* temp2=node1->dep;
                     if(temp2==NULL)
                    {
                     node1->dep=dep1;
                    }   
                   else
                   {
                    while(temp2->next)
                     {
                       temp2=temp2->next;
                     }
                    temp2->next=dep1;
                   }
                  // cout<<" creating dep node "<<"\n";
                   dep1->write_ref=a->write_ref;
                   dep1->read_ref.push_back(*i);
                 
                }
                j++;
              }
              b=b->next;
            }
              a=a->next;
           }
          temp=temp->next;
      }
 calculate_node(intersect_RAW);
    
}
void calculate_intersection_WAW(loop* node)
{   
    
       
      vector<SgNode*>::iterator i;
     
      
    
     loop* temp=node;
     while(temp)
      {
       
        loop* node1=new loop;
        node1->next=NULL;
        node1->dep=NULL;
        if(intersect_WAW==NULL)
        {
           
        intersect_WAW=node1;
        }
        else
        { //cout<<" creating new node "<<"\n";
           loop* temp1=intersect_WAW;
        while(temp1->next)
          {
            temp1=temp1->next;
          }
        temp1->next=node1;
        }
       
           node1->loop_number=temp->loop_number;
          dep_data* a=temp->dep;

           while(a)
           {
              dep_data* b=a->next;
               int j=0;
              while(b)
              {
              for(i=b->write_ref.begin();i!=b->write_ref.end();i++)
              {   string a1=a->write_ref[0]->unparseToString();
                  string b1=(*i)->unparseToString();
                //  cout<<"a1 = "<<a1 <<"\n";
                 //  cout<<"b1 = "<<b1 <<"\n";
                 if(a1[0]==b1[0])
                 {
                 //  cout<<" in "<<"\n";
                  dep_data* dep1=new dep_data;
                  dep1->next=NULL;
                  dep1->statement_no=a->statement_no;
                  dep_data* temp2=node1->dep;
                     if(temp2==NULL)
                    {
                     node1->dep=dep1;
                    }   
                   else
                   {
                    while(temp2->next)
                     {
                       temp2=temp2->next;
                     }
                    temp2->next=dep1;
                   }
                  // cout<<" creating dep node "<<"\n";
                   dep1->write_ref=a->write_ref;
                   dep1->write_ref.push_back(*i);

                }
                  j++;
              }
              b=b->next;
            }
              a=a->next;
           }
          temp=temp->next;
      }
// calculate_node(intersect_RAW);
    
}
/*vector<string> instersection_write(vector<string> &v1, vector<string> &write,vector<string> &v)
{

    vector<string> v3;

   // sort(v1.begin(), v1.end());
    
    // sort(write.begin(),write.end());
     vector<string>::iterator is,ie,i1s,i1e,readitr,writeitr,output;
     is=v1.begin();
     ie=v1.end();
     writeitr=write.begin();
     if(is==ie)
      return v;
    int i,j;
   for(i=0;i<v1.size();i++)
   {
     for(j=i+1;j<v1.size();j++)
     {
        if(v1.at(i)==v1.at(j))
        {
       //   cout<<"value "<<v1.at(i);
        //  cout<<" write "<<write.at(i);
          v.push_back(write.at(i));
          
        }
     }
   }
   return v;
}
*/
void ref_function(SgNode* for_loop,SgFunctionDefinition *defn )
{
    SgForStatement* forLoop=isSgForStatement(for_loop);
    SgBasicBlock* loopBody = isSgBasicBlock(forLoop->get_loop_body());
    
   vector<SgNode*> reads;
   vector<SgNode*> writes;
   vector<string> read;
   vector<string> write;
   vector<string> read_ref;
   vector<string> write_ref;
   SgExpression* rhs;
   SgExpression* lhs;
   vector<string>::iterator ik;
    if(loopBody!=NULL)
    {    vector<SgNode*>:: iterator itr;
         Rose_STL_Container<SgStatement*> forLoops = loopBody->get_statements();
       //  cout<<"print loop statements "<<"\n";
         
          loop* node=new loop;

         if(head==NULL)
         {
          
           head=node;
         }
         else
         {
         loop* temp=head;
          while(temp->next)
          {
            temp=temp->next;
          }
          temp->next=node;
         }
        node->loop_number=i++;
        node->next=NULL;
        node->dep=NULL;
        int k=0;
         for(Rose_STL_Container<SgStatement*>::iterator iter = forLoops.begin(); iter!= forLoops.end(); iter++ )
         { 
          SgScopeStatement* scope=(*iter)->get_scope();
         // cout<<" statements are "<< (*iter)->unparseToString()<<"\n";
           
          SageInterface::collectReadWriteRefs(*iter, reads, writes);
           dep_data* dep1=new dep_data;
             dep1->next=NULL;
             dep1->statement_no=k++;
           dep_data* temp=node->dep;
            if(temp==NULL)
            {
             
              node->dep=dep1;
            }   
            else
            {
                 while(temp->next)
                 {
                  temp=temp->next;
                 }
                 temp->next=dep1;
            }   
          for (itr=reads.begin();itr!=reads.end();itr++)
           {
                if(isSgBinaryOp(*itr)!=NULL)
                {
                   rhs = isSgBinaryOp(*itr)->get_rhs_operand();
                   lhs=  isSgBinaryOp(*itr)->get_lhs_operand();
                   
                //    cout<<"itr "<<(*itr)->unparseToString();
               //   cout<<"read Ref "<<(lhs)->unparseToString()<<"["<<(rhs)->unparseToString()<<"]"<<endl;
                  string a=(lhs)->unparseToString()+"["+(rhs)->unparseToString()+"]";
                 
               dep1->read_ref.push_back(*itr);
             //  dep1->read_size.push_back((rhs)->unparseToString());
                  //read.push_back(a);

                }
           }
            for (itr=writes.begin();itr!=writes.end();itr++)
           {
                if(isSgBinaryOp(*itr)!=NULL)
                {
                   rhs = isSgBinaryOp(*itr)->get_rhs_operand();
                   lhs=  isSgBinaryOp(*itr)->get_lhs_operand();
                 
                //  cout<<"write Ref "<<(lhs)->unparseToString()<<"["<<(rhs)->unparseToString()<<"]"<<endl;
                  string a=(lhs)->unparseToString()+"["+(rhs)->unparseToString()+"]";
                  dep1-> write_ref.push_back(*itr);
                 
               //   write_ref.push_back((lhs)->unparseToString());

                }

           }
           reads.clear();
           writes.clear();
         }
         
           
           
        /*   calculate_intersection(head);
           cout<<"after intersection "<<"\n";
         display(intersect_RAW);*/
          
         /* cout<<"statement number "<<i<<"\n";
                  i++;
          for (itr=reads.begin();itr!=reads.end();itr++)
           {
                if(isSgBinaryOp(*itr)!=NULL)
                {
                   rhs = isSgBinaryOp(*itr)->get_rhs_operand();
                   lhs=  isSgBinaryOp(*itr)->get_lhs_operand();
                  
                  cout<<"read Ref "<<(lhs)->unparseToString()<<"["<<(rhs)->unparseToString()<<"]"<<endl;
                  string a=(lhs)->unparseToString()+"["+(rhs)->unparseToString()+"]";
                  read_ref.push_back((lhs)->unparseToString());
                  read.push_back(a);

                }
           }
         */
        
         

       
       
         vector<string> v;
        /* cout<<"write_ref"<<"\n";
          for (ik=write_ref.begin(); ik!=write_ref.end(); ++ik)
                 std::cout << ' ' << *ik<<"\n";
               cout<<"write"<<"\n";
          for (int i=0; i<write.size(); ++i)
                 std::cout << ' ' << write.at(i)<<"\n";*/
     /*   instersection_read(read_ref,write_ref,read,write,v);
       std::cout << "The RAW set has " << (v.size()) << " elements:\n";
           for (ik=v.begin(); ik!=v.end(); ++ik)
                 std::cout << ' ' << *ik<<"\n";
                 v.clear();
        instersection_write(write_ref,write,v);
      
       std::cout << "The WAW set has " << (v.size()) << " elements:\n";
           for (ik=v.begin(); ik!=v.end(); ++ik)
                 std::cout << ' ' << *ik<<"\n";*/
  

    }

}
/*int main(int argc, char * argv[])
{
     vector<SgNode*> readRefs;
     vector<SgNode*> writeRefs;
     vector<SgNode*>:: iterator itr;
    SgProject *project = frontend (argc, argv);
    SgFunctionDeclaration* func = SageInterface::findMain(project);
    visitorTraversal ae;
    ae.traverseInputFiles(project,preorder);
     display(head_loop);
    SgFunctionDefinition *defn = func->get_definition();
    Rose_STL_Container<SgNode*> forLoops = NodeQuery::querySubTree(defn,V_SgForStatement);
    for(Rose_STL_Container<SgNode*>::iterator iter = forLoops.begin(); iter!= forLoops.end(); iter++ )
    {
        // printf ("Found a SgForStatement \n");
         
        
        ref_function(*iter,defn);

/*         for(iter1 = pntrArrRefList.begin(); iter1 != pntrArrRefList.end(); ++iter1) 
         {

          if(a!=NULL)
          { cout<<"abc"<<"\n";  
            if(isAssignmentStatement(a,NULL,NULL))
              cout<<"found statement"<<"\n";
          }
          
          
     
         }*/
   
    /*}

    
 display(head);
calculate_intersection_RAW(head);
cout<<"after intersection  RAW"<<"\n";
display(intersect_RAW);
calculate_intersection_WAW(head);
cout<<"after intersection  WAW"<<"\n";
display(intersect_WAW);

int k= GCD_Test(intersect_RAW,intersect_WAW,head_loop);
 }*/
