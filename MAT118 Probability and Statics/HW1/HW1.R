read_data <- function(filename){
  data <- read.csv(filename)
  return(data)
}


countryNumber <- function(txns){#1
  cat("Number of Country :")
  cat(length(unique(txns$location)))
  cat("\n")
}
q_2 <- function(data){
  cat("earliest Countries and date :")
  cat(c(data[data$date == min(data$date),"location"],",",min(data$date)))
  cat("\n")
  }

confirmedCasesForEachCountry <- function(data){#3
  cat("country,Case\n")
  locations <- unique(data$location)
  for(i in 1:length(locations)){
    cat(c(locations[i],",",sum(data[data$location == locations[i] ,"new_cases"])))
    cat("\n")
    }
}

confirmedDeathsForEachCountry <- function(data){#4
  cat("country,Death\n")
  locations <- unique(data$location)
  for(i in 1:length(locations)){
    cat(c(locations[i],",",sum(data[data$location == locations[i] ,"new_deaths"])))
    cat("\n")
    }
}
totalNum <- function(data , string, location){
  res <- data[data$location == location ,string]
  res1 <- c()
  for(j in 1 :length(res)){
    if(is.na(res[j])){
      
    }
    else res1 <- c(res1,res[j]) 
  }
  return(res1[length(res1)])
}

fourVal <- function(arr){
  if(length(arr) == 0){
    return(c("",",","",",","",",",""))
  }
  return(c(min(arr),",",max(arr),",",mean(arr),",",var(arr)))
}

eveluate <- function(data,string,location){
  res <- data[data$location == location ,string]
  #cat(res)
  res1 <- c()
  for(j in 1 :length(res)){
    if(is.na(res[j])){
      
    }
    else res1 <- c(res1,res[j]) 
  }

  return(res1)
}

q_5 <- function(data){
  cat("country,Min,Max,Avarage,Varidation,(reproduction_rate)\n")
  locations <- unique(data$location)
  for(i in 1:length(locations)){
    res <- eveluate(data,"reproduction_rate",locations[i]) 
    if(length(res) != 0)
      {
      cat(c(locations[i],",",min(res),",",max(res),",",mean(res),",",var(res)))
      cat("\n")
      }
    }
}


q_6 <- function(data){
  cat("country,Min,Max,Avarage,Varidation,(icu_patients)\n")
  locations <- unique(data$location)
  for(i in 1:length(locations)){
    res <- eveluate(data,"icu_patients",locations[i]) 
    if(length(res) != 0)
      {cat(c(locations[i],",",min(res),",",max(res),",",mean(res),",",var(res)))
    cat("\n")}
    }
}


q_7 <- function(data){
  cat("country,Min,Max,Avarage,Varidation,(hosp_patients)\n")
  locations <- unique(data$location)
  for(i in 1:length(locations)){
    res <- eveluate(data,"hosp_patients",locations[i]) 
    if(length(res) != 0)
      {cat(c(locations[i],",",min(res),",",max(res),",",mean(res),",",var(res)))
    cat("\n")}
    }
}


q_8 <- function(data){
  cat("country,Min,Max,Avarage,Varidation,(weekly_icu_admissions)\n")
  locations <- unique(data$location)
  for(i in 1:length(locations)){
    res <- eveluate(data,"weekly_icu_admissions",locations[i]) 
    if(length(res) != 0)
      {cat(c(locations[i],",",min(res),",",max(res),",",mean(res),",",var(res)))
    cat("\n")}
    }
}


q_9 <- function(data){
  cat("country,Min,Max,Avarage,Varidation,(weekly_hosp_admissions)\n")
  locations <- unique(data$location)
  for(i in 1:length(locations)){
    res <- eveluate(data,"weekly_hosp_admissions",locations[i]) 
    if(length(res) != 0)
      {cat(c(locations[i],",",min(res),",",max(res),",",mean(res),",",var(res)))
    cat("\n")}
  }
}

q_10 <- function(data){
  cat("country,Min,Max,Avarage,Varidation,(new_tests)\n")
  locations <- unique(data$location)
  for(i in 1:length(locations)){
    res <- eveluate(data,"new_tests",locations[i]) 
    if(length(res) != 0)
      {cat(c(locations[i],",",min(res),",",max(res),",",mean(res),",",var(res)))
    cat("\n")}
  }
}

q_11 <- function(data){
  cat("country,tests are conducted in total\n")
  locations <- unique(data$location)
  for(i in 1:length(locations)){
    res <- data[data$location == locations[i] ,"new_tests"]
    #cat(res)
    res1 <- c()
    for(j in 1 :length(res)){
      if(is.na(res[j])){
        
      }
      else res1 <- c(res1,res[j]) 
    }
    #cat(res1)
    if(length(res1) != 0)
      {cat(c(locations[i],",",sum(res1)))
    cat("\n")}
  }
}

q_12 <- function(data){
  cat("country,Min,Max,Avarage,Varidation,(positive_rate)\n")
  locations <- unique(data$location)
  for(i in 1:length(locations)){
    res <- eveluate(data,"positive_rate",locations[i]) 
    if(length(res) != 0)
      {cat(c(locations[i],",",min(res),",",max(res),",",mean(res),",",var(res)))
    cat("\n")}
  }
}

q_13 <- function(data){
  cat("country,Min,Max,Avarage,Varidation,(tests_per_case)\n")
  locations <- unique(data$location)
  for(i in 1:length(locations)){
    res <- eveluate(data,"tests_per_case",locations[i]) 
    if(length(res) != 0){
      cat(c(locations[i],",",min(res),",",max(res),",",mean(res),",",var(res)))
      cat("\n")
    }
      
  }
}


q_14 <- function(data){
  cat("country, people are vaccinated\n")
  locations <- unique(data$location)
  for(i in 1:length(locations)){
    cat(c(locations[i],",",totalNum(data,"total_vaccinations",locations[i])))
    cat("\n")
  }
}
q_15 <- function(data){
  cat("country, people are vaccinated fully\n")
  locations <- unique(data$location)
  for(i in 1:length(locations)){
    cat(c(locations[i],",",totalNum(data,"people_fully_vaccinated",locations[i])))
    cat("\n")
  }
}
q_16 <- function(data){
  cat("country,vaccinations are administered\n")
  locations <- unique(data$location)
  for(i in 1:length(locations)){
    cat(c(locations[i],",",totalNum(data,"total_vaccinations",locations[i])+totalNum(data,"people_fully_vaccinated",locations[i])))
    cat("\n")
  }
}

q_17 <- function(data){
  cat("Country,Population,Median_Age,Older_65,Older_70,Economic,Heart_Dissase,Diabetes,Smoker_F,Smoker_M,Handwash_Hospital_Bed,Life_Expectancy,Human_Development\n")
  locations <- unique(data$location)
  for(i in 1:length(locations)){
    res <- data[data$location == locations[i] ,"population"]
    res1 <-data[data$location == locations[i] ,"median_age"]
    res2 <-data[data$location == locations[i] ,"aged_65_older"]
    res3 <- data[data$location == locations[i] ,"aged_70_older"]
    res4 <-data[data$location == locations[i] ,"gdp_per_capita"]
    res5 <-data[data$location == locations[i] ,"cardiovasc_death_rate"]
    res6 <- data[data$location == locations[i] ,"diabetes_prevalence"]
    res7 <-data[data$location == locations[i] ,"female_smokers"]
    res8 <-data[data$location == locations[i] ,"male_smokers"]
    res9 <- data[data$location == locations[i] ,"handwashing_facilities"]
    res10 <-data[data$location == locations[i] ,"hospital_beds_per_thousand"]
    res11 <-data[data$location == locations[i] ,"life_expectancy"]
    res12 <-data[data$location == locations[i] ,"human_development_index"]
    
    cat(c(locations[i],",",res[length(res)],",",res1[length(res1)],",",res2[length(res2)],",",res3[length(res3)],",",res4[length(res4)],",",res5[length(res5)],",",res6[length(res6)],",",res7[length(res7)],",",res8[length(res8)],",",res9[length(res9)],",",res10[length(res10)],",",res11[length(res11)],",",res12[length(res12)]))
    cat("\n")
  }
}

q_18 <- function(data){
  cat("Country,total_cases,total_deaths,min,max,avaragage,variation(reproduction_rate),min,max,avaragage,variation(icu_patients),min,max,avaragage,variation(hosp_patients),min,max,avaragage,variation(weekly_icu_admissions),min,max,avaragage,variation(weekly_hosp_admissions),min,max,avaragage,variation(new_tests),total_tests,min,max,avaragage,variation(positive_rate),min,max,avaragage,variation(tests_per_case),people_vaccinated,total_vaccinations,Population,Median_Age,Older_65,Older_70,Economic,Heart_Dissase,Diabetes,Smoker_F,Smoker_M,Handwash,Hospital_Bed,Life_Expectancy,Human_Development\n")
  locations <- unique(data$location)
    for(i in 1:length(locations)){
    res <- data[data$location == locations[i] ,"population"]
    res1 <-data[data$location == locations[i] ,"median_age"]
    res2 <-data[data$location == locations[i] ,"aged_65_older"]
    res3 <- data[data$location == locations[i] ,"aged_70_older"]
    res4 <-data[data$location == locations[i] ,"gdp_per_capita"]
    res5 <-data[data$location == locations[i] ,"cardiovasc_death_rate"]
    res6 <- data[data$location == locations[i] ,"diabetes_prevalence"]
    res7 <-data[data$location == locations[i] ,"female_smokers"]
    res8 <-data[data$location == locations[i] ,"male_smokers"]
    res9 <- data[data$location == locations[i] ,"handwashing_facilities"]
    res10 <-data[data$location == locations[i] ,"hospital_beds_per_thousand"]
    res11 <-data[data$location == locations[i] ,"life_expectancy"]
    res12 <-data[data$location == locations[i] ,"human_development_index"]
    q16 <- totalNum(data,"total_vaccinations",locations[i])+totalNum(data,"people_fully_vaccinated",locations[i])
    q15 <- totalNum(data,"people_fully_vaccinated",locations[i])
    q14 <- totalNum(data,"total_vaccinations",locations[i])
    
    q13 <- eveluate(data,"tests_per_case",locations[i]) 
    q12 <- eveluate(data,"positive_rate",locations[i]) 
    q10_11 <-res <- eveluate(data,"new_tests",locations[i]) 
    q9<-eveluate(data,"weekly_hosp_admissions",locations[i]) 
    q8<-eveluate(data,"weekly_icu_admissions",locations[i]) 
    q7<-eveluate(data,"hosp_patients",locations[i]) 
    q6<-eveluate(data,"icu_patients",locations[i]) 
    q5<-eveluate(data,"reproduction_rate",locations[i]) 
    q4<-sum(data[data$location == locations[i] ,"new_deaths"])
    q3<-sum(data[data$location == locations[i] ,"new_cases"])
    
    prt <- c(locations[i],",",q3,",",q4,",",fourVal(q5),",",fourVal(q6),",",fourVal(q7),",",fourVal(q8),",",fourVal(q9),",",fourVal(q10_11),",",sum(q10_11),",",fourVal(q12),",",fourVal(q13),",",q14,",",q15,",",q16,",",res[length(res-1)],",",res1[length(res1)],",",res2[length(res2)],",",res3[length(res3)],",",res4[length(res4)],",",res5[length(res5)],",",res6[length(res6)],",",res7[length(res7)],",",res8[length(res8)],",",res9[length(res9)],",",res10[length(res10)],",",res11[length(res11)],",",res12[length(res12)])
    
    cat(prt)
    cat("\n")
    }
  }


data <- read_data("datanew.csv")
sink("output.csv")
countryNumber(data)
q_2(data)
confirmedCasesForEachCountry(data)
confirmedDeathsForEachCountry(data)
q_5(data)
q_6(data)
q_7(data)
q_8(data)
q_9(data)
q_10(data)
q_11(data)
q_12(data)
q_13(data)
q_14(data)
q_15(data)
q_16(data)
q_17(data)
q_18(data)
sink()

