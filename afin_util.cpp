// Worker function

#include <iostream>
#include "afin_util.hpp"
#include "contig.hpp"
#include "queue.tcc"

// Consume function which will act as the driver for an individual thread
void thread_worker(vector<Contig>& contigs, Queue<int>& q, unsigned int id) {
  for (int i = 0;; ++i) {
    auto item = q.pop();
    if( item == -1 ){
      break;
    }
    else{
      contigs[item].extend( false );
      contigs[item].extend( true );
    }
  }
}

// PRINT USAGE FUNCTION
void print_usage( string prog ){
  cout << "Usage: " << prog << " -c contigfile(s) -r readfile(s) [-o outfile] [-m max_sort_char] [-s contig_sub_len]" << endl;
  cout << "          [-l max_search_loops] [-i min_cov_init] [-p min_overlap] [-t max_threads]" << endl;
  cout << "       " << prog << " -h" << endl;
  cout << endl;
  cout << "  -c contigfile(s)     Comma separated list of files containing contigs" << endl;
  cout << "  -r readfile(s)       Comma separated list of files containing reads" << endl;
  cout << "  -o outfile           Output will be printed to the outfile specified with a .fasta extension" << endl;
  cout << "  -m max_sort_char     [default:   4] Sorts the reads by the first max_sort_char characters" << endl;
  cout << "  -s contig_sub_len    [default: 100] Will focus on the current last contig_sub_len characters of the contig in each search" << endl;
  cout << "  -l max_search_loops  [default:  10] Will search against each contig a maximum of max_search_loops times before comparing them" << endl;
  cout << "  -i min_cov_init      [default:   5] Will stop adding bp's once the coverage falls below min_cov_init" << endl;
  cout << "  -p min_overlap       [default:  20] Only those reads overlapping the contig by at least min_overlap bp's will be returned in each search" << endl;
  cout << "  -t max_threads       [default:   6] Will only run max_threads threads at a time" << endl << endl;
}
