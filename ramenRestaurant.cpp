//submit this file

#include "ramenRestaurant.h"
#include "noodle.h"
#include "soup.h"
#include "pork.h"
#include <iostream>
#include <vector>
using std::cout;
using std::endl;

RamenRestaurant::RamenRestaurant(int ingredientStorageCapacity) : ingredientStorageCapacity(ingredientStorageCapacity)
{
    ingredientStorage = new Ingredient*[ingredientStorageCapacity]; //create a dynamic array of Ingredient pointers, of size ingredientStorageCapacity
    for(int i=0; i<ingredientStorageCapacity; i++) //we should set all ingredientStorage slots to nullptr's since our storage is literally empty at the beginning
        ingredientStorage[i] = nullptr;
}

RamenRestaurant::~RamenRestaurant()
{
    //Hint: use "delete" for non-array dynamic objects, and use "delete []" for dynamic arrays
    int i = 0;
    for(; i < ingredientStorageCapacity;i++){
        delete ingredientStorage[i];
    }
    delete ingredientStorage;


}

bool RamenRestaurant::isStorageFull()
{
    return ingredientStorageUsed == ingredientStorageCapacity;
}

void RamenRestaurant::addFoodToStorage(Ingredient* food)
{
    for(int i = 0; i < ingredientStorageCapacity; i++)
    {
        if(ingredientStorage[i] == nullptr) //check if we have found the first non-empty storage slot
        {
            ingredientStorage[i] = food; //add the ingredient to that slot then
            break; //this is important to stop our loop here: what would happen if we don't?
        }
    }
    ingredientStorageUsed++; //update the state
}

bool RamenRestaurant::prepareNoodle(int softness)
{
    if(isStorageFull()) //cannot prepare new noodles when the storage is full
    {
        cout << "Whoops! No more storage space for the new noodle! :(" << endl;
        return false;
    }
    addFoodToStorage(new Noodle(softness)); //prepare it and store it
    cout << "Noodle (" << softness << "% softness) has been prepared and added to storage! :)" << endl;
    return true;
}

bool RamenRestaurant::prepareSoup(int spiciness)
{
    if(isStorageFull()) //cannot prepare new soup when the storage is full
    {
        cout << "Whoops! No more storage space for the new soup! :(" << endl;
        return false;
    }
    addFoodToStorage(new Soup(spiciness)); //prepare it and store it
    cout << "Soup (" << spiciness << "% spiciness) has been prepared and added to storage! :)" << endl;
    return true;
}

bool RamenRestaurant::preparePork()
{
    if(isStorageFull()) //cannot prepare new pork when the storage is full
    {
        cout << "Whoops! No more storage space for the new pork! :(" << endl;
        return false;
    }
    addFoodToStorage(new Pork()); //prepare it and store it
    cout << "Pork has been prepared and added to storage! :)" << endl;
    return true;
}

        bool RamenRestaurant::prepareAndServeRamen(int requiredNoodleSoftness, int requiredSoupSpiciness, bool doublePork)
{
    //TODO: implement this function
    /*
        Hint:
        ingredientStorage[i] is merely an Ingredient pointer.
        Therefore, you cannot directly use it like a Noodle pointer even though the object it points to is actually a Noodle object. For example, the following won't compile:
            cout << ingredientStorage[i]->getSoftness() << endl;
        In C++, you can use dynamic_cast for trying to cast it to a Noodle pointer like this:
            Noodle* realNoodlePointer = dynamic_cast<Noodle*>(ingredientStorage[i]);
        The good thing about dynamic_cast is that it gives you a nullptr if the casting fails when ingredientStorage[i] doesn't really point to a Noodle object. It is useful for checking what object it is pointing to. Of course, before you do dynamic_cast, you should make sure ingredientStorage[i] is not really a nullptr itself first.
    */
    /*
        Please copy and use the following for the success message:
        cout << "Ramen has been skillfully prepared and happily served! :)" << endl;

        Please copy and use the following for the failure message:
        cout << "Oh no, we cannot prepare the ramen requested! :(" << endl;
    */
    Noodle* noodle = nullptr;
    Soup* soup = nullptr;
    Pork* pork = nullptr;
    Pork* pork2 = nullptr;
    std:: vector<int> d_array(4,-1);

    for( int i = 0; i < ingredientStorageCapacity; i++){
        if (!(ingredientStorage[i]->isGood())) {
            continue;
        }
        noodle = (noodle == nullptr) ? dynamic_cast<Noodle *> (ingredientStorage[i]) : noodle;
        noodle = (noodle != nullptr && noodle->getSoftness() < requiredNoodleSoftness) ? nullptr : noodle;

        soup = (soup == nullptr) ? dynamic_cast<Soup *> (ingredientStorage[i]): soup;
        soup = (soup != nullptr && soup->getSpiciness()< requiredSoupSpiciness) ? nullptr: soup;
        pork = (pork == nullptr) ? dynamic_cast<Pork *> (ingredientStorage[i]): pork;
        pork2 = (pork2 == nullptr && doublePork) ? dynamic_cast<Pork *> (ingredientStorage[i]): pork2;
        pork2 = (pork2 == pork) ? nullptr: pork2;
        d_array[0] = (d_array[0] == -1 && noodle != nullptr) ? i : d_array[0];
        d_array[1] = (d_array[1] == -1 && soup != nullptr) ? i : d_array[1];
        d_array[2] = (d_array[2] == -1 && pork != nullptr) ? i : d_array[2];
        d_array[3] = (d_array[3] == -1 && pork2 != nullptr) ? i : d_array[3];

    }
    if(noodle == nullptr || soup == nullptr || pork == nullptr || ((pork2 == nullptr )&& doublePork)) {
        cout << "Oh no, we cannot prepare the ramen requested! :(" << endl;
        return false;
    }
    for(int i = 0; i < 4; i++){
        ingredientStorage[d_array[i]] = nullptr;
    }
    noodle = nullptr;
    soup = nullptr;
    pork = nullptr;
    pork2 = nullptr;
    delete noodle;
    delete soup;
    delete pork;
    if (doublePork){
        delete pork2;
        ingredientStorageUsed--;
    }
    ingredientStorageUsed -= 3;
    ramenServed++;
    cout << "Ramen has been skillfully prepared and happily served! :)" << endl;
    return true;
}

void RamenRestaurant::update()
{
    //update the states for each of the ingredients stored
    for(int i = 0; i < ingredientStorageCapacity; i++)
        if(ingredientStorage[i] != nullptr) //of course, we have to make sure the current storage slot is not really empty
            ingredientStorage[i]->update(); //so update it
}

void RamenRestaurant::print()
{
    cout << "Currently, we have " << ingredientStorageUsed << " ingredient" << (ingredientStorageUsed!=1?"s":"") << " in the restaurant storage: " << endl;
    for(int i = 0; i < ingredientStorageCapacity; i++) //go through our whole ingredient storage
    {
        cout << "Slot " << i << ": ";
        if(ingredientStorage[i] == nullptr) //nullptr means an empty slot at index i
            cout << "empty";
        else
            ingredientStorage[i]->print(); //invoke the print function for the ingredient - it will call the correct function (Noodle's or Soup's) depending on the actual class of the object the pointer points to: it is a dynamic binding
        cout << endl;
    }
    cout << "And... " << ramenServed << " bowl" << (ramenServed!=1?"s":"") << " of Hellish Teemo Ramen proudly served so far!" << endl;
    cout << endl;
}
