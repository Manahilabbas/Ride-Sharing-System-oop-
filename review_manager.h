#ifndef REVIEW_MANAGER_H
#define REVIEW_MANAGER_H

#include <string>
#include <vector>
#include "driver_review.h"

class ReviewManager {
public:
    static void saveReviewToFile(const std::string& driverName, const DriverReview& review);
    static void loadReviews(const std::string& driverName, std::vector<DriverReview>& reviews);
};

#endif
