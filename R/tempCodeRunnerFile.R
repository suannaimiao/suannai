library("rpart")
dt<-function(data,n,form){
  require(rpart)
  for(i in 1:1000){
    ind<-sample(1:nrow(data),round(0,7*nrow(data)),replace = FALSE)
    treemodel<-rpart(form,data[ind,],method = "class")
    #得到模型
    treepre<-predict(treemodel,data[-ind,-n],type="class")
    #根据模型
    t<-table(data[-ind,n],treepre)
    accu[i]<-sum(diag(t))/sum(t)
  }
  return(c(mean(accu),sd(accu)))
  ##统计1000次模型准确率和标准差（稳定性）
} 