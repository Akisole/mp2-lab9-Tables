
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

public:
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

	bool Find(TKey k) {
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
			if ((freepos == -1) && arr[curr].key == "&") {
				freepos = curr;
				curr +=(curr+step)%size;
			}
		}
		return false;
	}
	void Delete(TKey k) {
		if(Find(k)) {
			arr[case].key = '&';
			DataCount--;
		}
	}
	void Reset(){
		curr =  0;
		while ((arr[curr].key == "&" || arr[curr].key == " ") && curr<size)
			curr++;
	}

};

template <class TKey, class TValue>
struct TNode 
{
	int bal;
	TRecord<TKey, TValue> rec;
	TNode *pLeft, *pRight;
};