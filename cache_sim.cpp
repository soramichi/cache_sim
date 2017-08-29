#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

class Cache {
private:

  int num_slots;
  unsigned long** sets;
  int n_sets;
  int way;

public:

  Cache(unsigned long size_kb, int _way){
    this->way = _way;
    this->n_sets = (size_kb * 1024) / (way * 64);
    this->sets = (unsigned long**)malloc(sizeof(unsigned long*) * n_sets);

    for(int i=0; i<this->n_sets; i++) {
      this->sets[i] = (unsigned long*)malloc(sizeof(unsigned long) * way);
    }
  }

  ~Cache(){
    for(int i=0; i<this->n_sets; i++) {
      free(this->sets[i]);
    }
    free(this->sets);
  }

  void print_slot(int slot) {
    printf("current state of slot %d: ", slot);
    for(int i=0; i<way; i++) {
      printf("0x%x ", this->sets[slot][i]);
    }
    printf("\n");
  }
  
  bool load(unsigned long addr){
    unsigned long line_addr = addr / 64;
    int target_set = line_addr & (n_sets - 1);
    unsigned long tag = line_addr / n_sets;

    for(int i=0; i<way; i++) {
      if(this->sets[target_set][i] == tag) {
	//  <- new   i     -> old
	// index 0 1 2 3 4 5
	// data  a b c d e f
	//   =>  c a b d e f
	for(int j=i; j>0; j--) {
	  sets[target_set][j] = sets[target_set][j-1];
	}
	sets[target_set][0] = tag; // bring the hit data to the top
	return true; // hit
      }
    }

    for(int i=way-1; i>0; i--) {
      //  <- new         -> old
      // index 0 1 2 3 4 5
      // data  a b c d e f
      //   =>  g a b c d e  
      sets[target_set][i] = sets[target_set][i-1];
    }
    sets[target_set][0] = tag;
    return false; // miss
  }
};

// input:
//   a file containing the accessed addresses in the hex format (0x12345),
//   one address per line
int main(){
  Cache cache(4096, 16); // 4096KB, 16 way set associative

  int n_hit = 0, n_miss = 0;
  char buff[128];

  while(fgets(buff, sizeof(buff), stdin)) {
    unsigned long addr;
    bool hit;

    addr = strtol(buff+2, NULL, 16); // "0x123ab" + 2 => "123ab"    
    hit = cache.load(addr);
    if(hit) {
      n_hit++;
    }
    else {
      n_miss++;
    }
  }

  printf("n_hit: %d, n_miss: %d, sum: %d\n", n_hit, n_miss, n_hit + n_miss);
  printf("hit_rate: %.5f\n", (double)n_hit / (n_hit + n_miss));
  
  return 0;
}
