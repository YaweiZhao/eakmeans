#ifndef PLL_EXACTSIMPLEBATCHKMEANS_H
#define PLL_EXACTSIMPLEBATCHKMEANS_H

#include "basesimpleexact.h"



namespace kmeans{

template <typename TInt, typename TFloat>
class SimpleExactBatchKmeans : public kmeans::BaseSimpleExactKmeans<TInt, TFloat>{
	
	private:
		TInt nperbatch;

	public:
		TInt get_nperbatch(){
			return this->nperbatch;
		}
		
		template<typename... Args>
		SimpleExactBatchKmeans(Args&&... args): kmeans::BaseSimpleExactKmeans<TInt, TFloat> (std::forward<Args>(args)...) {
			this->setalgname("Exact Simple Batch K-Means");
			//set so that the batch step does not cause memory in assigment to exceed half memory of data itself			
			nperbatch = std::max(
			static_cast<TInt> (1), static_cast<TInt> ((this->getndata() * this->getdimension())/(2 * this->getncentroids() * this->nthreads))
			);
		}				
	
		virtual ~SimpleExactBatchKmeans(){};
		

	protected:
		virtual void set_X_tasks(){
			this->X_tasks = {
				arrutilv2::update_L_S_H_batch_ati(this->getnthreads(), this->getndata(), this->nperbatch, this->getdimension(), this->getdata(), this->getncentroids(), this->get_C(), this->get_data_l22s(), this->get_C_l22s(), this->get_L(), this->get_dsums(), this->get_dcounts(), this->get_sums(), this->get_counts(), this->nchanges, this->work_mutex, this->ndcalcs_X)
			};
			
			
			//update_L_S_H_batch_ati(TInt nthreads, TInt ndata, TInt nperbatch, TInt dimension, const TFloat * const data, TInt ncentroids, const TFloat * const C, const TFloat * const data_l22s, const TFloat * const C_l22s, TInt * const L, TFloat * const dsums, TInt * const dcounts, TFloat * const sums, TInt * const counts, TInt & nchanges, std::mutex & work_mutex, std::atomic<TInt> & ndcalcs){
				
				
		}	
};
	
}



#endif



//extern template class kmeans::SimpleExactBatchKmeans<size_t, double>;
//extern template class kmeans::SimpleExactBatchKmeans<size_t, float>;


