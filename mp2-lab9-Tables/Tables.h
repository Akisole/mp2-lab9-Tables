#include "Stack.h"

template <class TKey, class TValue>
struct TRecord
{
	TKey key;
	TValue val;
};

template <class TKey, class TValue>
class TTable 
{
protected:
	int DataCount;
	int Eff;
	int pos;

public:
	TTable() {
		DataCount = 0;
		Eff = 0;
	}
	bool IsEmpty() const {
		if (DataCount == 0) 
			return true;
		else 
			return false;
	}

	virtual bool IsFull() const = 0;
	virtual bool Find(TKey k) = 0;
	virtual void Insert(TRecord<TKey, TValue> r) = 0;
	virtual void Delete(TKey k) = 0;
	virtual void Reset() = 0;
	virtual void GoNext() = 0;
	virtual bool IsEnd() = 0;
	virtual TRecord<TKey, TValue> GetCurrent() = 0;
	virtual void Print ()
	{
		TRecord<TKey, TValue> tmp;
		for (Reset(); !IsEnd(); GoNext()) {
			tmp = GetCurrent();
			std::cout << tmp.key << tmp.val << std::endl;
		}
	}

};

template <class TKey, class TValue>
class TArrayTable: public TTable<TKey, TValue> 
{
protected:
	TRecord<TKey, TValue>* arr;
	int maxSize;
	int curr;

public:
	TArrayTable(int max_Size = 100) {
		maxSize = max_Size;
		curr = 0;
		arr = new TRecord<TKey, TValue>[maxSize];
	}
	~TArrayTable() { delete[] arr;}
	//констр коп + присваивание

	virtual void Reset { return curr = 0; }
	virtual void GoNext() { return curr += 1; }
	virtual bool IsEnd() {
		if (curr == DataCount ) return true;
		else return false; 
	}
};

template <class TKey, class TValue>
class TScanTable : public TArrayTable <TKey, TValue>
{
	TScanTable (); //конструктор написать

	virtual bool Find (TKey k) {
		for (int i=0; i<DataCount; i++) {
			if (arr[i].key == k) {
				curr = i;
				return true;
			}
			Eff++;
		}
		curr = DataCount;
		return false;
	}
	virtual bool Insert (TRecord<TKey, TValue> tr) {
		if (!Find(tr.key) {
			arr[curr] = tr;
			DataCount++;
			return true;
		}
		return false;
	}
	virtual void Delete (TKey k) {
		if (Find(k)) {
			arr[curr] = arr[DataCount-1];
			DataCount--;
		}
	}
};

template <class TKey, class TValue>
class TSortTable : public TArrayTable <TKey, TValue> 
{
	TSortTable(); //конструктор написать

	virtual bool Find (TKey k) {
		int l=0, r=DataCount-1, m;
		while (l<=r) {
			Eff++;
			m=*l+r)/2;
			if(arr[m].key = k) {
				curr = m;
				return true;
			}
			if (arr[m].key < k)
				l=m+1;
			else
				r=m-1;
		}
		curr = l;
	    return false;
	}
	virtual bool Insert (TRecord<TKey, TValue> tr) {
		if(!Find(tr.key) {
			for (int i=DataCount; i>curr; i--) {
				arr[i] = arr[i-1];
				Eff++;
			}
			arr[curr] = tr;
			DataCount++;
			return true;
		}
		return false;
	}
	virtual void Delete (TKey k) {
		if(Find(k) {
			for (int i=curr; i<DataCount-1; i++) {
				arr[i] = arr[i+1];
				Eff++;
			}
			DataCount--;
		}
	}

	void Sort (int l, int r) {
		int m=(l+r)/2, i=l, j=r;
		TKey mkey = arr[m].key;
		while(i<=j) {
			Eff++;
			while (arr[i].key < mkey) {
				Eff++;
				i++;
			}
			while (arr[j].key > mkey) {
				Eff++;
				j--;
			}
			if (i <= j) {
				TKey tmp = arr[j];
				arr[j] = arr[i];
				arr[i] = tmp;
			}
		}
		if (j>l)
			Sort(l, j);
		if (i<r) 
			Sort(i, r);
	}
};

template <class TKey, class TValue>
class THashTable: public TTable<Tkey, Tvalue>
{
protected:
	int HashFunc(TKey k) {
		int pos = 0;
		for(int i=0; i<k.lenght(); i++)
			pos += k[i]<<i;
		return pos;
	}
};

template <class TKey, class TValue>
class TArrayHash: public THashTable<TKey, TValue>
{
protected:
	int size, step, curr;
	TRecord<TKey, TValue>* arr;

public:
	TArrayHash(int _size = 100) {
		size = _size;
		step = 13; //?
		arr = new TRecord<TKey,TValue>[size];
		for(int i = 0; i<size; i++)
			arr[i] = " ";
	}

	virtual bool Find(TKey k) {
		curr = HashFunc(k)%size;
		int freepos = -1;
		for( int i=0; i<size; i++) {
			Eff++;
			if(arr[curr].key == " "){
				if(freepos == -1)
					return false;
				else {
					curr = freepos;
					return false;
				}
			}
			if(arr[curr].key == k)
				return true;
			if ((freepos == -1) && arr[curr].key == "&") 
				freepos = curr;
			curr +=(curr+step)%size; //?
		}
		return false;
	}
	virtual void Delete(TKey k) {
		if(Find(k)) {
			arr[case].key = '&';
			DataCount--;
		}
	}
	virtual void Reset(){
		curr =  0;
		while ((arr[curr].key == "&" || arr[curr].key == " ") && curr<size)
			curr++;
	}
	// Insert делаем Find, если не найдено, то на карент добавляем, иначе двигаем на шаг
	// Reset() подстав curr на 1 не пустую (while)
	// GoNext так же как Reset, но не будет curr=0, а будет curr++
	// IsEnd() Curr=DataCount
};

template <class TKey, class TValue>
struct TNode 
{
	int bal;
	TRecord<TKey, TValue> rec;
	TNode *pLeft, *pRight;
};

template <class TKey, class TValue>
class TreeTable: public  TTable<TKey, TValue> 
{
protected:
	TNode *pRoot, *pCurr, **pRes;
	TStack<TNode*> st;
public:
	TreeTable() {
		pRoot = pCurr = pRes = NULL;
	}
	virtual bool Find(TKey k) {
		*pRes = pRoot;
		while (*pRes != NULL) {
			Eff++;
			if ((*pRes)->rec.key == k)
				return true;
			else {
				if((*pRes)->rec.key < k)
					pRes = &(*pRes->pRight);
				else 
					pRes = &(*pRes->pLeft);
			}
		}
		return false;
	}
	virtual void Insert(TRecord<TKey, TValue> r) {
		if (!Find(r.key)){
			TNode *tmp = new TNode<TKey, TValue>;
			tmp->rec = r;
			tmp->pLeft = NULL;
			tmp->pRight = NULL;
			*pRes = tmp;
		}
	}
	virtual void Delete(TKey k) {
		if (Find(k)) {
			TNode *tmp = *pRes;
			if(tmp->pLeft == NULL)	*pRes = tmp->pRight;
			else {
				if (tmp->pRight == NULL)	*pRes = tmp->pLeft;
				else {
					TNode *p = tmp->pLeft, **pPrev = &(tmp->pLeft);
					while (p->pRight != NULL) {
						Eff++;
						pPrev = &(p->pRight);
						p = p->pRight;
					}
					tmp->rec = pRes;
					tmp = p;
					*pPrev = p->pLeft;
				}
				delete tmp;
			}
		}
	}
	virtual void Reset() {
		pos = 0;
		st.Clear();
		pCurr = pRoot;
		while (pCurr->pLeft != NULL) {
			st.Push(pCurr);
			pCurr = pCurr->pLeft;
		}
	}
	virtual void GoNext() {
		if(pCurr->pRight != NULL) {
			pCurr = pCurr->pRight;
			while (pCurr->pLeft != NULL) {
				st.Push(pCurr);
				pCurr = pCurr->pLeft;
			}
		}
		else {
			if (!st.IsFull()) //?
				pCurr = st.Pop();
		}
		pos++;
	}
	virtual bool IsEnd() {
		if (pos == DataCount)
			return true;
		else
			return false;
	}
	void Print (pRoot *Curr) {
		if(Curr->pLeft) Print(Curr->pLeft);
		cout << pNode->rec;
	} //говно какоето
};