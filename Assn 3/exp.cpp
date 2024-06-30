#include "CubicProbing.h"
using namespace std;
void merge(std::vector<int> &arr, int start, int mid, int end)
{
    const int len1 = mid - start + 1;
    const int len2 = end - mid;
    std::vector<int> v1(len1);
    std::vector<int> v2(len2);
    for (int i = 0; i < len1; i++)
    {
        v1[i] = arr[start + i];
    }
    for (int j = 0; j < len2; j++)
    {
        v2[j] = arr[mid + 1 + j];
    }
    int i = 0, j = 0, k = start;
    while (i < len1 && j < len2)
    {
        if (v1[i] <= v2[j])
        {
            arr[k++] = v1[i++];
        }
        else
        {
            arr[k++] = v2[j++];
        }
    }
    while (i < len1)
    {
        arr[k++] = v1[i++];
    }
    while (j < len2)
    {
        arr[k++] = v2[j++];
    }
}

void mergeSort(std::vector<int> &arr, int start, int end)
{
    if (end - start < 1)
    {
        return;
    }
    int mid = (start + end) / 2;
    mergeSort(arr, start, mid);
    mergeSort(arr, mid + 1, end);
    merge(arr, start, mid, end);
}

CubicProbing::CubicProbing()
{
    dataBaseSize = 0;
    hashPrimeIndex = 0;
    capacity = hashprimes[hashPrimeIndex];
    Account acc;
    acc.id = "-1";
    acc.balance = -1;
    for (int i = 0; i < capacity; i++)
    {
        BaseClass::bankStorage1d.push_back(acc);
    }
}

int CubicProbing::createAccount(std::string id, int count)
{
    // IMPLEMENT YOUR CODE HERE
    Account acci;
    acci.id = id;
    acci.balance = count;
    if (hashPrimeIndex != 10 && dataBaseSize == capacity / 2)
    {
        Account acc;
        acc.id = "-1";
        acc.balance = -1;
        capacity = hashprimes[++hashPrimeIndex];
        std::vector<Account> aux;
        for (int i = 0; i < capacity; i++)
        {
            aux.push_back(acc);
        }
        int prevlen = hashprimes[hashPrimeIndex - 1];
        for (int i = 0; i < prevlen; i++)
        {
            int hashvalue;
            if (BaseClass::bankStorage1d[i].id != "-1")
            {
                hashvalue = hash(BaseClass::bankStorage1d[i].id);
            }
            else
            {
                continue;
            }
            int j = 0;
            while (aux[(hashvalue + ((((j * j) % capacity) * j) % capacity)) % capacity].balance != -1)
            {
                // hashvalue=(hashvalue+((j*j)%capacity))%capacity;
                j++;
            }
            aux[(hashvalue + ((((j * j) % capacity) * j) % capacity)) % capacity] = BaseClass::bankStorage1d[i];
        }
        // BaseClass::bankStorage2d.clear();
        BaseClass::bankStorage1d = aux;
    }
    int hashvalue = hash(id);
    int j = 0;
    while (BaseClass::bankStorage1d[(hashvalue + ((((j * j) % capacity) * j) % capacity)) % capacity].balance != -1)
    {
        // hashvalue = (hashvalue + ((j*j)%capacity)) % capacity;
        j++;
    }
    BaseClass::bankStorage1d[(hashvalue + ((((j * j) % capacity) * j) % capacity)) % capacity] = acci;
    dataBaseSize++;
    return (hashvalue + ((((j * j) % capacity) * j) % capacity)) % capacity;
}

std::vector<int> CubicProbing::getTopK(int k)
{
    // IMPLEMENT YOUR CODE HERE
    std::vector<int> v, ans;
    for (int i = 0; i < capacity; i++)
    {
        v.push_back(BaseClass::bankStorage1d[i].balance);
    }
    mergeSort(v, 0, capacity - 1);
    for (int i = 1; i <= k; i++)
    {
        ans.push_back(v[capacity - i]);
    }
    return ans; // Placeholder return value
}

int CubicProbing::getBalance(std::string id)
{
    // IMPLEMENT YOUR CODE HERE
    int hashvalue = hash(id);
    // int j=1;
    for (int j = 0; j < capacity; j++)
    {
        if (BaseClass::bankStorage1d[(hashvalue + ((((j * j) % capacity) * j) % capacity)) % capacity].id == id)
        {
            return BaseClass::bankStorage1d[(hashvalue + ((((j * j) % capacity) * j) % capacity)) % capacity].balance;
        }
        // else{
        //     hashvalue = (hashvalue + ((j * j)%capacity)) % capacity;
        // }
    }
    return -1;
    // return 0; // Placeholder return value
}

void CubicProbing::addTransaction(std::string id, int count)
{
    // IMPLEMENT YOUR CODE HERE
    int hashvalue = hash(id);
    // int j=1;

    for (int j = 0; j < capacity; j++)
    {
        if (BaseClass::bankStorage1d[(hashvalue + ((((j * j) % capacity) * j) % capacity)) % capacity].id == id)
        {
            BaseClass::bankStorage1d[(hashvalue + ((((j * j) % capacity) * j) % capacity)) % capacity].balance += count;
            return;
        }
        // else{
        //     hashvalue = (hashvalue + ((j * j)%capacity)) % capacity;
        // }
    }
    createAccount(id, count);
    return;
}

bool CubicProbing::doesExist(std::string id)
{
    // IMPLEMENT YOUR CODE HERE
    int hashvalue = hash(id);
    // int j=1;
    bool bol = false;
    for (int j = 0; j < capacity; j++)
    {
        if (BaseClass::bankStorage1d[(hashvalue + ((((j * j) % capacity) * j) % capacity)) % capacity].id == id)
        {
            bol = true;
            break;
        }
        // else{
        //     hashvalue = (hashvalue + ((j * j)%capacity)) % capacity;
        // }
    }
    return bol; // Placeholder return value
}

bool CubicProbing::deleteAccount(std::string id)
{
    // IMPLEMENT YOUR CODE HERE
    int hashvalue = hash(id);
    bool bol = false;
    for (int j = 0; j < capacity + 5; j++)
    {
        // if (BaseClass::bankStorage1d[hashvalue].id=="-1"){
        //     return false;
        // }
        if (BaseClass::bankStorage1d[(hashvalue + ((((j * j) % capacity) * j) % capacity)) % capacity].id == id)
        {
            dataBaseSize--;
            BaseClass::bankStorage1d[(hashvalue + ((((j * j) % capacity) * j) % capacity)) % capacity].id = "-1";
            BaseClass::bankStorage1d[(hashvalue + ((((j * j) % capacity) * j) % capacity)) % capacity].balance = -1;
            bol = true;
            break;
        }
        // else{
        //     hashvalue = (hashvalue + ((j * j)%capacity)) % capacity;
        // }
    }

    if (hashPrimeIndex != 0)
    {
        if (dataBaseSize <= hashprimes[hashPrimeIndex - 1] / 4)
        {

            capacity = hashprimes[--hashPrimeIndex];
            std::vector<Account> aux;
            for (int i = 0; i < capacity; i++)
            {
                Account acc;
                acc.id = "-1";
                acc.balance = -1;
                aux.push_back(acc);
            }

            int prevlen = hashprimes[hashPrimeIndex + 1];
            for (int i = 0; i < prevlen; i++)
            {
                if (BaseClass::bankStorage1d[i].id != "-1")
                {
                    int hashvalue = hash(BaseClass::bankStorage1d[i].id);
                    int j = 0;
                    while (aux[(hashvalue + ((((j * j) % capacity) * j) % capacity)) % capacity].id != "-1")
                    {
                        // hashvalue=(hashvalue+((j*j)%capacity))%capacity;
                        j++;
                    }
                    aux[(hashvalue + ((((j * j) % capacity) * j) % capacity)) % capacity] = BaseClass::bankStorage1d[i];
                }
            }
            BaseClass::bankStorage1d = aux;
        }
    }

    return bol; // Placeholder return value
}
int CubicProbing::databaseSize()
{
    // IMPLEMENT YOUR CODE HERE
    return dataBaseSize; // Placeholder return value
}

int CubicProbing::hash(std::string id)
{
    // IMPLEMENT YOUR CODE HERE
    int len = id.size();
    int prime1 = hashprimes[hashPrimeIndex];
    int prime2 = 37;
    int hashvalue = 0;
    int curr = 1;
    for (int i = 0; i < len; i++)
    {
        hashvalue = (hashvalue + curr * (id[i])) % prime1;
        curr = (curr * prime2) % prime1;
    }
    return hashvalue; // Placeholder return value
}



int main(){
    CubicProbing obj;
    cout << obj.createAccount("ABCD0000000_1234567890", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234567809", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234567980", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234567908", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234567089", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234567098", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234568790", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234568709", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234568970", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234568907", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234568079", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234568097", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234569780", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234569708", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234569870", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234569807", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234569078", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234569087", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234560789", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234560798", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234560879", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234560897", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234560978", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234560987", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234576890", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234576809", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234576980", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234576908", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234576089", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234576098", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234578690", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234578609", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234578960", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234578906", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234578069", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234578096", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234579680", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234579608", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234579860", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234579806", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234579068", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234579086", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234570689", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234570698", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234570869", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234570896", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234570968", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234570986", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234586790", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234586709", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234586970", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234586907", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234586079", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234586097", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234587690", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234587609", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234587960", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234587906", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234587069", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234587096", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234589670", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234589607", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234589760", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234589706", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234589067", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234589076", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234580679", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234580697", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234580769", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234580796", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234580967", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234580976", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234596780", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234596708", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234596870", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234596807", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234596078", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234596087", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234597680", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234597608", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234597860", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234597806", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234597068", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234597086", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234598670", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234598607", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234598760", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234598706", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234598067", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234598076", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234590678", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234590687", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234590768", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234590786", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234590867", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234590876", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234506789", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234506798", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234506879", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234506897", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234506978", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234506987", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234507689", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234507698", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234507869", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234507896", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234507968", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234507986", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234508679", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234508697", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234508769", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234508796", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234508967", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234508976", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234509678", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234509687", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234509768", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234509786", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234509867", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234509876", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234657890", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234657809", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234657980", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234657908", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234657089", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234657098", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234658790", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234658709", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234658970", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234658907", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234658079", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234658097", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234659780", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234659708", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234659870", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234659807", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234659078", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234659087", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234650789", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234650798", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234650879", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234650897", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234650978", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234650987", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234675890", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234675809", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234675980", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234675908", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234675089", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234675098", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234678590", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234678509", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234678950", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234678905", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234678059", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234678095", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234679580", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234679508", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234679850", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234679805", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234679058", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234679085", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234670589", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234670598", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234670859", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234670895", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234670958", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234670985", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234685790", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234685709", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234685970", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234685907", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234685079", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234685097", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234687590", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234687509", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234687950", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234687905", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234687059", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234687095", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234689570", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234689507", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234689750", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234689705", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234689057", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234689075", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234680579", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234680597", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234680759", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234680795", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234680957", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234680975", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234695780", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234695708", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234695870", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234695807", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234695078", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234695087", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234697580", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234697508", 123) << "\n";
    cout << obj.createAccount("ABCD0000000_1234697850", 123) << "\n";
    cout<<"size: "<<obj.dataBaseSize<<" capacity: "<<obj.capacity<<"\n";
    cout << obj.deleteAccount("ABCD0000000_1234567890") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234567809") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234567980") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234567908") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234567089") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234567098") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234568790") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234568709") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234568970") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234568907") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234568079") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234568097") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234569780") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234569708") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234569870") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234569807") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234569078") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234569087") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234560789") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234560798") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234560879") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234560897") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234560978") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234560987") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234576890") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234576809") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234576980") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234576908") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234576089") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234576098") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234578690") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234578609") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234578960") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234578906") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234578069") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234578096") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234579680") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234579608") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234579860") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234579806") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234579068") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234579086") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234570689") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234570698") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234570869") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234570896") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234570968") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234570986") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234586790") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234586709") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234586970") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234586907") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234586079") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234586097") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234587690") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234587609") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234587960") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234587906") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234587069") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234587096") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234589670") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234589607") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234589760") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234589706") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234589067") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234589076") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234580679") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234580697") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234580769") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234580796") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234580967") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234580976") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234596780") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234596708") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234596870") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234596807") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234596078") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234596087") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234597680") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234597608") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234597860") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234597806") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234597068") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234597086") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234598670") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234598607") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234598760") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234598706") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234598067") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234598076") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234590678") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234590687") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234590768") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234590786") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234590867") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234590876") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234506789") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234506798") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234506879") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234506897") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234506978") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234506987") << "\n";
    //cout<<obj.createAccount("234",2)<<"\n";
    cout << "size: " << obj.dataBaseSize << " capacity: " << obj.capacity << "\n";
    cout << obj.createAccount("ABCD0000000_1234568970",1234) << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234568907") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234568079") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234568097") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234569780") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234569708") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234569870") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234569807") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234569078") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234569087") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234560789") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234560798") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234560879") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234560897") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234560978") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234560987") << "\n";
    cout << obj.createAccount("ABCD0000000_1234576890",1) << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234576809") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234576980") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234576908") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234576089") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234576098") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234578690") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234578609") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234578960") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234578906") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234578069") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234578096") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234579680") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234579608") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234579860") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234579806") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234579068") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234579086") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234570689") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234570698") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234570869") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234570896") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234570968") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234570986") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234586790") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234586709") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234586970") << "\n";
    cout << obj.deleteAccount("ABCD0000000_1234586907") << "\n";
    cout << "size: " << obj.dataBaseSize << " capacity: " << obj.capacity << "\n";
}
