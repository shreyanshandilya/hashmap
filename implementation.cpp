#include<bits/stdc++.h>
using namespace std;

template<typename V>
class MapNode {
    public:
        string key;
        V value;
        MapNode* next;
        MapNode(string key, V value) {
            this->key = key;
            this->value = value;
            this->next = NULL;
        }
        ~MapNode() {
            delete next;
        }
};

template<typename V>
class MyMap {
    private:
        MapNode<V>** buckets;
        int count;
        int numBuckets;
        int getBucketIndex(string key) {
            int res = 0;
            int base = 1;
            int p = 31;
            for(int i=key.size()-1; i>=0; i--) {
                res += key[i] * base;
                base = base * p;
                res = res%numBuckets; 
                base = base%numBuckets;
            }
            return res; 
        }
        void rehashing() {
            MapNode<V>** temp = buckets;
            buckets = new MapNode<V>*[2*numBuckets];
            int oldSize = numBuckets;
            numBuckets *= 2;
            for(int i=0; i<numBuckets; i++) {
                buckets[i] = NULL;
            }
            count = 0;
            for(int i=0; i<oldSize; i++) {
                MapNode<V>* head = temp[i];
                while(head!=NULL) {
                    insert(head->key, head->value);
                    head = head->next;
                }
            }
            for(int i=0; i<oldSize; i++) {
                delete temp[i];
            }
            delete []temp;
        }
    public:
        MyMap() {
            count = 0;
            numBuckets = 5;
            buckets = new MapNode<V>*[numBuckets];
            //Initialize everything to null
            for(int i=0; i<numBuckets; i++) {
                buckets[i] = NULL;
            }
        }
        ~MyMap() {
            for(int i=0; i<numBuckets; i++) {
                delete buckets[i];
            }
            delete []buckets;
        }
        int size() {
            return count;
        }
        void insert(string key, V value) {
            int bucketIndex = getBucketIndex(key);
            MapNode<V>* head = buckets[bucketIndex];
            while(head!=NULL) {
                if(head->key==key) {
                    head->value = value;
                    return;
                }
                head = head->next;
            }
            MapNode<V>* node = new MapNode<V>(key, value);
            node->next = buckets[bucketIndex];
            buckets[bucketIndex] = node;
            count++;
            double loadFactor = (1.0*count)/numBuckets;
            if(loadFactor>0.7) {
                rehashing();
            }
        }
        V remove(string key) {
            int index = getBucketIndex(key);
            MapNode<V>* head = buckets[index];
            MapNode<V>* prev = NULL;
            while(head!=NULL) {
                if(head->key==key) {
                    if(prev==NULL) {
                        buckets[index] = head->next;
                    }
                    else {
                        prev->next = head->next;
                    }
                    V value = head->value;
                    head->next = NULL;
                    delete head;
                    count--;
                    return value;
                }
                prev = head;
                head = head->next;
            }
            return 0;
        }
        V search(string key) {
            int index = getBucketIndex(key);
            MapNode<V>* head = buckets[index];
            while(head!=NULL) {
                if(head->key==key) {
                    return head->value;
                }
                head = head->next;
            }
            return 0;
        }
        double getLoadFactor() {
            return (1.0*count)/numBuckets;
        }
};

int main() {
    MyMap<int> a;
    string key = "";
    int value = 0;
    for(int i=0; i<26; i++) {
        key += 'a'+i;
        a.insert(key,value);
        cout << a.getLoadFactor() << endl;
        value++;
    }
    key = "";
    for(int i=0; i<26; i++) {
        key += 'a'+i;
        cout << key << " " << a.search(key) << endl;
    }
    return 0;
}