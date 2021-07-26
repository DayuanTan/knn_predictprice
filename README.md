# knn_predictprice

This program is used for me to predict stock price using knn algorithm based on the data I prepare in https://github.com/DayuanTan/prepare_data_4knn

At first I have lots of history price and I make each 10 as a set and in each set I have 9 price changes. 

'test' file is my sketch edition. Data in all_stockschanges_5yr_apart.csv file is ordered by 'open prices changes; high prices changes; low prices changes; close prices changes; volume prices changes; name'. I read 9 days' 8 price changes which are just before the predicted day form '9days_8changes_b4_predictedday.csv' and then read one set form 'all_stockschanges_5yr_apart.csv', and use only first 8 price changes of its 9 price changes, and then compute the distance between them two and I have a distance. Then I read another one set form 'all_stockschanges_5yr_apart.csv', and also use only first 8 price changes of its 9 price changes, and then compute the distance between them two and I have another distance...... At last I have lots of distance, I choice the set which has least distance. Then I can use the 10th price change of that set as the price change between the 9th day's price and the predicted day's price. So I can use the change and 9th day's price to calculate the predicted day's price.


# Report:
[here](CMSC%20611%20Project%20Report.pdf)
