#include "../include/nested_loop_join_executor.h"

NestedLoopJoinExecutor::NestedLoopJoinExecutor(
    AbstractExecutor *left_child_executor,
    AbstractExecutor *right_child_executor, const std::string join_key)
    : left_(left_child_executor),
      right_(right_child_executor),
      join_key_(join_key){};

void NestedLoopJoinExecutor::Init() {
    left_->Init();

    if (array.empty()){
        Tuple left_tuple;
        while (left_->Next(&left_tuple)){
            right_->Init();
            Tuple right_tuple;
            
            while(right_->Next(&right_tuple)){
                
                bool j = false;
                if (join_key_ == "val1"){
                    if(left_tuple.val1 == right_tuple.val1){
                        j = true;
                    }
                }else if (join_key_ == "val2"){
                    if(left_tuple.val2 == right_tuple.val2){
                        j = true;
                    }
                }else if (join_key_ == "id"){
                    if(left_tuple.id == right_tuple.id){
                        j = true;
                    }
                }

                if(j){array.emplace_back(left_tuple);}
            }
        }
    }

    iter_ = array.begin();
}

bool NestedLoopJoinExecutor::Next(Tuple *tuple) {
    if (iter_ != array.end()) {
        const Tuple &curr_tuple = *iter_;
        *tuple = Tuple(curr_tuple);
        ++iter_;
        return true;
    }
    return false;
}
