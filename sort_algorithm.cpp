#include <iostream>
//稳定排序：基数 归并 直接插入 冒泡
//冒泡排序
template <typename T>
void swap1(T* left, T* right){
	T tmp = *left;
	*left = *right;
	*right = tmp;
}

template <typename T>
void Bubble_sort(T* p, int len){
	for(int i = 0; i < len; i++){
		/*方向相反
		for(int j = len-1; j > i; j--){
			if(p[j] < p[j-1]){
				swap1<T>(&(p[j]), &(p[j-1]));
			}
		}*/
		for(int j = 1; j < len-i; j++){
			if(p[j] < p[j-1]){
				swap1<T>(&(p[j]), &(p[j-1]));
			}
		}
	}
}

//插入排序
template <typename T>
void Insert_sort(T *p, int len){

	for(int i = 1; i < len; i++){
		/*将两个for循环合并为一个
		for(int j = 0; j < i; j++){
			//为了是稳定排序，这里是'<'
			if(p[i] < p[j]){
				T tmp = p[i];
				for(int k = i; k > j; k--){
					p[k] = p[k-1];
				}
				p[j] = tmp;
			}
		}*/
		int tmp = p[i];
		int j = 0;
		//边比较边转移位子 j>-1 是为了该数字放在0的位子上
		for(j = i-1; j > -1 && tmp < p[j]; j--){
			p[j+1] = p[j];
		}
		p[j+1] = tmp;

	}
}

//选择排序

template <typename T>
void Choose_sort(T *p, int len){
	for(int i = 0; i < len; i++){
		int flag = i;
		for(int j = i+1; j < len; j++){
			if(p[flag] > p[j]){
				flag = j;
			}
		}
		//p[i] = p[flag];
		swap1(&(p[i]), &(p[flag]));
	}
}

//希尔排序,内部使用“直接插入排序”
template <typename T>
void Shell_Insert_sort(T *p, int len, int dk){
	for(int i = dk; i < 2*dk; i++){
		for(int j = i; j < len; j += dk){
			T tmp = p[j];
			int k = j - dk;
			while(k > -1 && tmp < p[k]){
				p[k+dk] = p[k];
				k = k-dk;
			}
			p[k+dk] = tmp;
		}
	}
}

template <typename T>
void Shell_sort(T *p, int len){
	for(int i = len/2; i > 0; i /= 2){
		Shell_Insert_sort<T>(p, len, i);
	}
}

//快速排序 得到划分值，然后进行分治排序
//在本改进算法中,只对长度大于k的子序列递归调用快速排序,让原序列基本有序，然后再对整个基本有序序列用插入排序算法排序。
//实践证明，改进后的算法时间复杂度有所降低，且当k取值为 8 左右时,改进算法的性能最佳。算法思想如下：
template <typename T>
int partition(T *p, int left, int right){
	int privot = p[left];
	while(left < right){
		while(right > left && privot < p[right]){right--;}
		//这里必须校验  privot 值在原位
		if(right > left){
			p[left] = p[right];
			left++;
		}
		while(left < right && privot > p[left]){left++;}
		if(right > left){
			p[right] = p[left];
			right--;
		}
	}
	p[left] = privot;
	return left;
}

template <typename T>
void Quick_sort(T *p, int left, int right){
	if(left < right){
		int privotloc = partition<T>(p, left, right);
		Quick_sort<T>(p, left, privotloc-1);
		Quick_sort<T>(p, privotloc+1, right);
	}
}
//归并排序
template <typename T>
void Merge(T *p, int left, int mid, int right){
	int len = right - left + 1;
	T *pnew = new T[len];
	int i = left; //左边数组开头
	int j = mid+1; //右边数组开头
	int k = 0;
	while (i <= mid && j <= right){
		if(p[i] <= p[j]){ //归并排序使稳定排序这里要加等号
			pnew[k++] = p[i++];
		}else{
			pnew[k++] = p[j++];
		}
	}
	while (i <= mid){
		pnew[k++] = p[i++];
	}
	while (j <= right){
		pnew[k++] = p[j++];
	}
	for(i = 0; i < len; i++){
		//注意下标
		p[left+i] = pnew[i];
	}
	delete [] pnew;
}

template <typename T>
void Merge_Rescurive_sort(T *p, int left, int right){
	if(left == right){//递归结束
		return;
	}
	int mid = (left+right)/2;
	Merge_Rescurive_sort(p, left, mid);
	Merge_Rescurive_sort(p, mid+1, right);
	Merge(p, left, mid, right);
}

//堆排序过程
/*
1. 由输入的无序数组构造一个最大堆，作为初始的无序区
2. 把堆顶元素(最大值)和堆尾元素互换
3. 把堆的尺度缩小为1，并用heapify(A,0)从新的堆顶元素开始进行调整
4. 重复步骤2，直到堆的尺寸为1	
*/

//从A[i]向下进行堆调整
template <typename T>
void Heapify(T *p, int i, int size){
	int left_child = 2*i+1;
	int right_child = 2*i+2;
	int max = i;  //选出当前节点与左右孩子三者之间的最大值
	if (left_child < size && p[left_child] > p[max]){
		max = left_child;
	}
	if (right_child < size && p[right_child] > p[max]){
		max = right_child;
	}
	if (max != i){
		swap1<T>(&p[i], &p[max]);
		//递归调用，继续从当前节点向下进行堆调整
		Heapify<T>(p, max, size);
	}
}

template <typename T>
int BuildHeap(T *p, int n){
	//建堆，时间复杂度为O(n)
	int heap_size = n;
	for(int i = (heap_size/2)-1; i >= 0; i--){
		//从每一个非叶子节点开始向下进行堆调整
		Heapify<T>(p, i, heap_size);
	}
	return heap_size;
}

template <typename T>
void Heap_sort(T *p, int n){
	int heap_size = BuildHeap(p, n);
	while (heap_size > 1){
		//将堆顶元素与堆的最后一个元素互换，并从对堆中去除最后一个元素
		swap1<T>(&p[0], &p[--heap_size]);
		Heapify<T>(p, 0, heap_size);
	}
}

//桶排序
template <typename T>
void show_array(T *p, int len){
	for(int i = 0; i < len; i++){
		std::cout << *(p+i) << ' ';
	}
	std::cout << std::endl;
}

int main(){
	int a[10] = {9,2,5,8,3,4,7,1,6,10};
	Heap_sort(a,10);
	show_array(a,10);
	return 0;
}