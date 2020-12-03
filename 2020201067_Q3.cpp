#include<bits/stdc++.h>
using namespace std;
#define PACKET_SIZE 100000


long long  min_heap[100000];
long long  file_index[100000];

void merge(long long  arr[], long long  l, long long  m, long long  r) 
{ 
    long long  i, j, k; 
    long long  n1 = m - l + 1; 
    long long  n2 = r - m; 

    long long  L[n1], R[n2]; 
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1 + j]; 
  
    i = 0; 
    j = 0; 
    k = l; 
    while (i < n1 && j < n2) { 
        if (L[i] <= R[j]) 
            arr[k++] = L[i++]; 
        else
            arr[k++] = R[j++]; 
    } 
    while (i < n1) 
        arr[k++] = L[i++]; 
    while (j < n2) 
        arr[k++] = R[j++]; 
} 
void m_sort(long long  arr[], long long  l, long long  r) 
{ 
    if (l < r) { 
        long long  m = l + (r - l) / 2; 
  
        m_sort(arr, l, m); 
        m_sort(arr, m + 1, r); 
  
        merge(arr, l, m, r); 
    } 
}
void Min_Heapify(long long  index, long long  size)
{
    long long  left_child = (2 * index) + 1;
    long long  right_child = (2 * index) + 2;
    long long  min_pos;
    if (left_child <= size - 1 && min_heap[left_child] < min_heap[index])
        min_pos = left_child;
    else
        min_pos = index;

    if (right_child <= size - 1 && min_heap[right_child] < min_heap[min_pos])
        min_pos = right_child;

    if (min_pos != index)
    {
        long long  temp = min_heap[index];
        min_heap[index] = min_heap[min_pos];
        min_heap[min_pos] = temp;

        long long  temp1 = file_index[index];
        file_index[index] = file_index[min_pos];
        file_index[min_pos] = temp1;
        Min_Heapify(min_pos, size);
    }
    return;
}

void create_heap(long long  s){
    for(long long  i = (s/2) + 2; i>=0;i--){
        Min_Heapify(i,s);
    }
}

void k_way_merge(char *out_file,long long  num_of_packet){
    FILE *final_out;
    final_out = fopen(out_file, "w");
    FILE* chunks[num_of_packet];
    for( long long  i=0;i<num_of_packet;i++){
        string f_name = to_string(i);
        chunks[i] = fopen(f_name.c_str(),"r");
    }
    long long  min_heap_size = num_of_packet;
    for( long long  i=0;i<num_of_packet;i++){
        long long  tmp;
        fscanf(chunks[i],"%lld",&tmp);
        if(!feof(chunks[i])){
            min_heap[i] = tmp;
            file_index[i] = i;
        } 
    }
    create_heap(min_heap_size);
    long long  iterator = 0;
    char del='a';
    while(iterator != num_of_packet){
        if(del=='a')
        fprintf(final_out,"%lld",min_heap[0]);
        else{
           fprintf(final_out,"%c",del);
           fprintf(final_out,"%lld",min_heap[0]);
        }
        del=',';
        long long  tmp_data;
        fscanf(chunks[file_index[0]],"%lld",&tmp_data);
        if(!feof(chunks[file_index[0]])){
            min_heap[0] = tmp_data;
        }
        else{
            min_heap[0] = LLONG_MAX;
            iterator++;
        }
        Min_Heapify(0,min_heap_size);
    }
    for( long long  i=0;i<num_of_packet;i++){
        fclose(chunks[i]);
        string s = to_string(i);
        remove( s.c_str() );
    }
    fclose(final_out);
}

void external_sort(char *inp_file, char *out_file){
    FILE* inp;
    inp = fopen(inp_file,"r");
    long long  data;
    long long  count=PACKET_SIZE;
    long long  int_file_name = 0;
    string f_name;
    FILE *outfile;
    long long  v[PACKET_SIZE];
    while(1){
	        if(fscanf(inp,"%lld,",&data) == EOF) break;
        if(count == PACKET_SIZE){
            f_name = to_string(int_file_name);
            int_file_name++;
            memset(v, 0,PACKET_SIZE*sizeof(long long ));
            outfile = fopen(f_name.c_str(),"w");
        }
        v[PACKET_SIZE-count] = data;
        count--;
        if(count == 0){
            m_sort(v,0,PACKET_SIZE-1);
            for( long long  i=0;i<PACKET_SIZE;i++) fprintf(outfile,"%lld ",v[i]);
            fclose(outfile);
            count = PACKET_SIZE;
        }
    }
    if(count != PACKET_SIZE){
            m_sort(v,0,PACKET_SIZE-count-1);
            for( long long  i=0;i<PACKET_SIZE-count;i++) fprintf(outfile,"%lld ",v[i]);
            fclose(outfile);
            count = PACKET_SIZE;
    }
    long long num_of_packet = int_file_name;
    fclose(inp);

    k_way_merge(out_file, num_of_packet);
}

int main(int argc, char * argv[]){
    external_sort(argv[1], argv[2]);
    return 0;
}