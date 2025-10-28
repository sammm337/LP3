## 1. Uber Fare Prediction (Regression)

This is a **supervised regression problem**. The goal is to predict a continuous numerical value (the fare price) based on input features (pickup/dropoff locations, time, etc.).

### 📖 Basic Theory

#### Task 1: Pre-processing the Dataset

* **What is it?** Pre-processing is the set of steps taken to clean and transform raw data into a format that is suitable for a machine learning model.
* **Why?** Models cannot work with raw, messy data. "Garbage in, garbage out."
* **Common Viva Questions:**
    * **Handling Missing Values:**
        * **Deletion:** Remove rows (listwise) or columns (pairwis) with missing values. This is only okay if you have a large dataset and a small percentage of missing data.
        * **Imputation:** Fill in missing values.
            * **Mean/Median:** For numerical features (e.g., fill missing 'passengers' with the median). Median is preferred if the data has outliers.
            * **Mode:** For categorical features (e.g., fill missing 'payment\_type' with the most common one).
    * **Handling Categorical Variables:** Models understand numbers, not text.
        * **One-Hot Encoding:** Creates new binary (0/1) columns for each category (e.g., `payment_type_cash`, `payment_type_card`). Use this when categories have no natural order.
        * **Label Encoding:** Assigns a unique integer to each category (e.g., Small=1, Medium=2, Large=3). Use this only if the categories have a meaningful order (ordinal data).
    * **Feature Scaling:** Puts all features on a similar scale.
        * **Standardization (Z-score):** Rescales data to have a mean of 0 and a standard deviation of 1 ($z = \frac{x - \mu}{\sigma}$). It's preferred for algorithms that assume a normal distribution, like Linear Regression.
        * **Normalization (Min-Max):** Rescales data to a fixed range, usually 0 to 1 ($x_{\text{norm}} = \frac{x - x_{\text{min}}}{x_{\text{max}} - x_{\text{min}}}$).
        * **Why is scaling important?** Algorithms that use gradient descent (like Linear Regression) or distance metrics (like KNN) converge much faster and perform better when features are scaled. Tree-based models (like Random Forest) are not sensitive to scaling.
    * **Feature Engineering:** Creating new, more informative features from existing ones. For this dataset, a crucial step would be:
        * **Calculating Distance:** Use the latitude and longitude of the pickup and dropoff points to calculate the **Haversine distance** (the great-circle distance between two points on a sphere). This single `distance` feature is likely the strongest predictor of `fare`.
        * **Date/Time Features:** Extract `hour_of_day`, `day_of_week`, `month`, and `year` from the timestamp. Fares might be higher during rush hour (high `hour_of_day`) or on weekends (different `day_of_week`).

#### Task 2: Identify Outliers

* **What is an outlier?** A data point that is significantly different from other data points. In this dataset, this could be a $0 fare, a $500 fare, or a ride with coordinates in the middle of the ocean.
* **Why identify them?** Outliers can heavily skew the results of models like Linear Regression, pulling the "best-fit" line in their direction.
* **How to identify them?**
    * **Visually:**
        * **Box Plots:** Show data distributed into quartiles. Points that fall outside the "whiskers" are considered outliers. The whiskers are typically defined as $1.5 \times \text{IQR}$ (Interquartile Range) below $Q1$ and above $Q3$.
        * **Scatter Plots:** Can reveal points that are far removed from the main cluster.
    * **Statistically:**
        * **Z-Score:** Any data point with a Z-score greater than 3 (or less than -3) is often considered an outlier, as it's 3 standard deviations from the mean.
        * **IQR Method:** The same method used by box plots ($< Q1 - 1.5 \times \text{IQR}$ or $> Q3 + 1.5 \times \text{IQR}$).

#### Task 3: Check the Correlation

* **What is it?** A statistical measure that describes the strength and direction of a **linear relationship** between two variables.
* **Pearson Correlation Coefficient ($r$):** The most common metric.
    * $r = 1$: Perfect positive linear correlation.
    * $r = -1$: Perfect negative linear correlation.
    * $r = 0$: No linear correlation.
* **Why check it?**
    1.  **Feature Selection:** To find which independent variables (like `distance`, `hour_of_day`) have a strong correlation with the dependent variable (`fare`).
    2.  **Detecting Multicollinearity:** This is when two or more *independent variables* are highly correlated with *each other* (e.g., $r > 0.8$). This is a problem for Linear Regression because it makes the model's coefficients unstable and hard to interpret.
* **How to visualize?** A **heatmap** of the correlation matrix is the standard way to see all correlations at a glance.

#### Task 4: Implement Models

* **Linear Regression**
    * **Theory:** A supervised learning algorithm that models a linear relationship between a dependent variable ($y$) and one or more independent variables ($x$).
    * **Equation:** $y = \beta_0 + \beta_1x_1 + \beta_2x_2 + \dots + \epsilon$
        * $y$: The predicted value (fare).
        * $\beta_0$: The intercept (the base fare when all $x$ values are 0).
        * $\beta_1, \beta_2 \dots$: The coefficients. Each $\beta$ represents the change in $y$ for a one-unit change in its corresponding $x$, holding all other variables constant.
        * $\epsilon$: The error term (residual).
    * **Goal:** To find the "best-fit" line by minimizing the **Sum of Squared Residuals (SSR)**—the sum of the squared differences between the actual $y$ and the predicted $y$. This is often done using an algorithm called **Ordinary Least Squares (OLS)**.
    * **Key Assumptions:**
        1.  **Linearity:** The relationship between $x$ and $y$ is linear.
        2.  **Independence:** The residuals (errors) are independent of each other.
        3.  **Homoscedasticity:** The residuals have constant variance.
        4.  **Normality:** The residuals are normally distributed.

* **Random Forest Regression**
    * **Theory:** An **ensemble learning** method. It works by building a large number of **decision trees** during training and outputting the **average** of their predictions.
    * **Core Concepts:**
        1.  **Ensemble:** It combines many "weak" models (decision trees) to create one "strong" model.
        2.  **Bootstrap Aggregation (Bagging):** Each tree is trained on a different random subset of the data (sampled *with replacement*). This ensures the trees are different from each other.
        3.  **Feature Randomness:** At each split in a tree, the algorithm only considers a random subset of the total features. This further decorrelates the trees.
    * **Pros:** Very high accuracy, robust to outliers, and doesn't require feature scaling. It can capture complex non-linear relationships that Linear Regression would miss.
    * **Cons:** Less interpretable (a "black box" model) and more computationally expensive than Linear Regression.

#### Model Evaluation & Comparison

* **$R^2$ (R-squared / Coefficient of Determination):**
    * **What:** The proportion of the variance in the dependent variable (`fare`) that is predictable from the independent variables (`distance`, `hour`).
    * **Range:** 0 to 1. A score of 0.75 means 75% of the variance in fares can be explained by your model's features. Higher is better.
* **Adjusted $R^2$:**
    * **What:** A modified $R^2$ that penalizes the model for adding features that don't improve it. It's more reliable when comparing models with different numbers of features.
* **RMSE (Root Mean Squared Error):**
    * **What:** The square root of the average of the squared errors. $\sqrt{\frac{1}{n}\sum(y_{\text{pred}} - y_{\text{actual}})^2}$
    * **Interpretation:** It's in the same units as the target variable (e.g., "$3.50"). It tells you the typical magnitude of your model's error. **It heavily penalizes large errors.** Lower is better.
* **MAE (Mean Absolute Error):**
    * **What:** The average of the absolute errors. $\frac{1}{n}\sum|y_{\text{pred}} - y_{\text{actual}}|$
    * **Interpretation:** Also in the same units as the target (e.g., "$2.75"). It's less sensitive to outliers than RMSE. Lower is better.

**Comparison:** Linear Regression is simple and interpretable, but Random Forest will likely be more accurate because fare pricing is complex and non-linear (e.g., prices surge during rush hour, a non-linear effect of time).

---

## 2. Email Spam Detection (Binary Classification)

This is a **supervised binary classification problem**. The goal is to classify an email as one of two categories: Spam (1) or Not Spam (0).

### 📖 Basic Theory

#### K-Nearest Neighbors (KNN)

* **Theory:** A simple, non-parametric, **lazy learning** algorithm.
* **"Lazy Learning":** It doesn't "learn" a model from the training data. It just stores the entire training dataset.
* **How it works (Prediction):**
    1.  To classify a new email, it looks at the **'$k$' closest emails** (the "neighbors") from the training set.
    2.  "Closeness" is measured using a distance metric, typically **Euclidean distance**.
    3.  The new email is assigned the class that is **most common** among its '$k$' neighbors (a "majority vote").
* **Pros:** Very simple to understand and implement.
* **Cons:**
    * Computationally slow at prediction time because it must compare the new point to *all* training points.
    * Very sensitive to the choice of '$k$'.
    * Performs poorly on high-dimensional data (like text data), known as the **"curse of dimensionality"**.
    * Requires feature scaling (Standardization/Normalization).

#### Support Vector Machine (SVM)

* **Theory:** A powerful classifier that finds the **optimal hyperplane** (a decision boundary) that best separates the two classes (Spam vs. Not Spam).
* **How it works:**
    1.  **Hyperplane:** In 2D, this is a line. In 3D, it's a plane. In higher dimensions, it's a hyperplane.
    2.  **Optimal Hyperplane:** The one that creates the **maximum margin** (the largest possible distance) between the hyperplane and the nearest data points from either class.
    3.  **Support Vectors:** The data points that lie *on* the margin. These are the critical points that "support" the hyperplane's position.
* **The Kernel Trick:**
    * **What if the data isn't linearly separable?** SVM can use **kernels** (e.g., RBF, Polynomial) to project the data into a higher-dimensional space where a linear hyperplane *can* be used to separate it. This is a very powerful concept.
* **Pros:**
    * Very effective in high-dimensional spaces (good for text).
    * Memory efficient (only uses the support vectors for prediction).
    * Versatile due to the kernel trick.
* **Cons:** Can be slow to train on very large datasets. Choosing the right kernel and hyperparameters (like '$C$') can be complex.

#### Performance Analysis

For classification, we use a **Confusion Matrix**:

| | **Predicted: Not Spam** | **Predicted: Spam** |
| :--- | :--- | :--- |
| **Actual: Not Spam** | True Negative (TN) | False Positive (FP) |
| **Actual: Spam** | False Negative (FN) | True Positive (TP) |

* **True Positive (TP):** Spam email correctly identified as Spam.
* **True Negative (TN):** Normal email correctly identified as Normal.
* **False Positive (FP) (Type I Error):** Normal email *incorrectly* marked as Spam. **This is the worst error** (you miss an important email).
* **False Negative (FN) (Type II Error):** Spam email *incorrectly* marked as Normal (you see a spam email in your inbox).

From this, we derive key metrics:
* **Accuracy:** $\frac{TP + TN}{\text{Total}}$. Overall, how many did we get right? (Can be misleading if classes are imbalanced, e.g., 99% of emails are Not Spam).
* **Precision:** $\frac{TP}{TP + FP}$. Of all emails we *predicted* as Spam, how many were *actually* Spam? **High precision is vital for spam detection** to avoid False Positives.
* **Recall (Sensitivity):** $\frac{TP}{TP + FN}$. Of all *actual* Spam emails, how many did we *catch*?
* **F1-Score:** $2 \times \frac{\text{Precision} \times \text{Recall}}{\text{Precision} + \text{Recall}}$. The harmonic mean of Precision and Recall. It provides a single score that balances both concerns.

---

## 3. Bank Customer Churn (Neural Network)

This is another **supervised binary classification problem** (Leave: 1, Stay: 0). The goal is to build an **Artificial Neural Network (ANN)**.

### 📖 Basic Theory

* **1. Read Dataset:** Load data into memory (e.g., pandas DataFrame).
* **2. Feature/Target Split & Train/Test Split:**
    * **Feature Set ($X$):** The inputs (CreditScore, Geography, Gender, Age, Balance, etc.).
    * **Target Set ($y$):** The output to predict (`Exited` column).
    * **Train/Test Split:** You must split your data (e.g., 80% train, 20% test).
        * **Why?** You train the model on the `train` set and then evaluate its *true* performance on the `test` set, which it has never seen before. This tells you if your model has **overfit** (memorized the training data) or if it can **generalize** to new, unseen data.
* **3. Normalize the Train and Test Data:**
    * **Why?** ANNs use Gradient Descent. Features with large scales (like `Balance`) will dominate the learning process over features with small scales (like `Tenure`). Scaling (especially **Standardization**) is **essential** for NNs to converge quickly and correctly.
    * **Critical Step:** You must **fit** the scaler (e.g., `StandardScaler`) **only on the training data** (`X_train`). Then, use that *same* fitted scaler to **transform** *both* `X_train` and `X_test`. This prevents **data leakage** (letting information from the test set "leak" into your training process).
* **4. Initialize and Build the Model (ANN):**
    * **What is an ANN?** A model inspired by the brain, made of layers of interconnected nodes (neurons).
    * **Architecture:**
        1.  **Input Layer:** One neuron for each input feature.
        2.  **Hidden Layers:** One or more layers that sit between the input and output. This is where the model learns complex patterns.
        3.  **Output Layer:** For binary classification, this is a single neuron with a **Sigmoid** activation function, which squashes the output to a probability between 0 and 1.
    * **Key Components:**
        * **Activation Function:** A non-linear function applied by neurons. **ReLU** (Rectified Linear Unit) is the most common for hidden layers because it's simple and avoids the "vanishing gradient" problem.
        * **Optimizer:** The algorithm that updates the model's weights to minimize loss. **Adam** is a highly effective and popular default choice.
        * **Loss Function:** The function to minimize. For binary classification, this is **Binary Cross-Entropy**.
* **5. Print Accuracy Score and Confusion Matrix:**
    * These are the same metrics as in Assignment 2. For a churn problem, the **False Negative (FN)** is very costly (predicting a customer will "Stay" when they actually "Leave"). **Recall** ($\frac{TP}{TP + FN}$) is a key metric here, as it measures your ability to "catch" the customers who are *actually* leaving.

---

## 4. Implement Gradient Descent

* **What is it?** An iterative **optimization algorithm** used to find the **local minima** of a function. It is the core algorithm used to train most machine learning models, including Linear Regression and Neural Networks.
* **Core Idea:**
    1.  Start at a random point on the function's curve.
    2.  Calculate the **gradient** (the derivative or slope) at that point. The gradient points in the direction of the *steepest ascent*.
    3.  Take a small step in the **opposite direction** of the gradient (i.e., downhill).
    4.  Repeat steps 2 and 3 until you reach the bottom (the gradient is zero or very close to it).
* **Update Rule:**
    $$x_{\text{new}} = x_{\text{old}} - \alpha \times f'(x_{\text{od}})$$
    * $x_{\text{old}}$: Your current position.
    * $\alpha$ (alpha): The **Learning Rate**. This is the *size* of the step you take.
        * If $\alpha$ is too **small**, the algorithm will be very slow.
        * If $\alpha$ is too **large**, you might "overshoot" the minimum and bounce around, failing to converge.
    * $f'(x_{\text{old}})$: The gradient (derivative) of the function at your current position.

* **Example: $y = (x+3)^2$ starting from $x=2$**
    1.  **Function:** $f(x) = (x+3)^2$
    2.  **Derivative (Gradient):** $f'(x) = 2(x+3)$
    3.  **Goal:** Find the $x$ that minimizes $y$. (We know the answer is $x = -3$, where $y = 0$).
    4.  **Let's choose $\alpha = 0.1$ and start at $x = 2$.**
        * **Iteration 1:**
            * $x = 2$
            * Gradient $f'(2) = 2(2+3) = 10$
            * $x_{\text{new}} = 2 - (0.1 \times 10) = 2 - 1 = 1$
        * **Iteration 2:**
            * $x = 1$
            * Gradient $f'(1) = 2(1+3) = 8$
            * $x_{\text{new}} = 1 - (0.1 \times 8) = 1 - 0.8 = 0.2$
        * **Iteration 3:**
            * $x = 0.2$
            * Gradient $f'(0.2) = 2(0.2+3) = 6.4$
            * $x_{\text{new}} = 0.2 - (0.1 \times 6.4) = 0.2 - 0.64 = -0.44$
    * As you can see, with each iteration, the value of $x$ moves from 2, to 1, to 0.2, to -0.44, getting progressively closer to the true minimum of -3.

---

## 5. K-Means Clustering

This is an **unsupervised learning problem**. You are not predicting a target; you are trying to *discover* natural groupings (clusters) in the sales data.

### 📖 Basic Theory

#### K-Means Clustering

* **Theory:** An iterative algorithm that partitions a dataset into '$k$' pre-defined, non-overlapping clusters.
* **How it works:**
    1.  **Initialize:** Choose the number of clusters, '$k$'. Randomly place '$k$' **centroids** (cluster centers) in your data.
    2.  **Assignment Step:** Assign each data point to its *nearest* centroid (usually based on Euclidean distance).
    3.  **Update Step:** Recalculate the position of each of the '$k$' centroids by taking the *mean* of all data points assigned to it.
    4.  **Repeat:** Repeat steps 2 and 3 until the centroids no longer move significantly (the model has converged).
* **Goal:** K-Means tries to minimize **Inertia**, also known as **WCSS** (Within-Cluster Sum of Squares). This is the sum of the squared distances between each point and its assigned cluster centroid.

#### Hierarchical Clustering (Alternative)

* **Theory:** An algorithm that builds a hierarchy of clusters.
* **How it works (Agglomerative):**
    1.  Starts with every data point as its own cluster.
    2.  Finds the two *closest* clusters and *merges* them.
    3.  Repeats step 2 until only one cluster (containing all data) remains.
* **Dendrogram:** This process is visualized using a **dendrogram** (a tree diagram). You can choose the number of clusters by cutting the dendrogram at a certain "height."

#### Determine the Number of Clusters: The Elbow Method

* **The Problem:** How do you know what '$k$' (the number of clusters) to choose?
* **The Elbow Method:** A heuristic to find the "optimal" '$k$'.
    1.  Run the K-Means algorithm for a range of '$k$' values (e.g., $k=1$ to $k=10$).
    2.  For each '$k$', calculate the **WCSS (Inertia)**.
    3.  Plot '$k$' (x-axis) vs. WCSS (y-axis).
    4.  The graph will look like an arm. As '$k$' increases, WCSS will always decrease. But at some point, the rate of decrease will slow down dramatically, creating a "bend" or "elbow" in the graph.
    5.  This **elbow point** is considered the optimal number of clusters, as it represents the point of diminishing returns (adding more clusters doesn't significantly reduce the WCSS).