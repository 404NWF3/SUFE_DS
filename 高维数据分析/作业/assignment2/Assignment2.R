# 高维数据分析 Assignment 2 -------------------------------------------------
# 顺序运行本文件即可重现第 1--9 题的数值和图表。
# 支持：在仓库根目录或本作业目录 source()，以及任意目录 Rscript /绝对路径/Assignment2.R。
# 首次使用若缺少包：install.packages(c("glmnet", "gglasso"))

# 0. 环境、路径与公共数据 ---------------------------------------------------
required_packages <- c("glmnet", "gglasso")
missing_packages <- required_packages[
  !vapply(required_packages, requireNamespace, logical(1), quietly = TRUE)
]
if (length(missing_packages)) {
  stop("请先安装缺少的 R 包：", paste(missing_packages, collapse = ", "))
}
library(splines)
set.seed(2026)
options(contrasts = c("contr.treatment", "contr.poly"))

script_file <- tryCatch(sys.frame(1)$ofile, error = function(e) NULL)
if (is.null(script_file)) {
  file_arg <- grep("^--file=", commandArgs(), value = TRUE)
  if (length(file_arg)) script_file <- sub("^--file=", "", file_arg[1])
}
candidates <- c(if (!is.null(script_file)) dirname(script_file),
                "assignments/高维数据分析/assignment2", ".")
valid_dirs <- candidates[file.exists(file.path(candidates, "hw2-2026-data/ais.csv"))]
if (!length(valid_dirs)) stop("找不到作业数据目录，请在仓库根目录或作业目录运行。")
assignment_dir <- normalizePath(valid_dirs[1])
data_dir <- file.path(assignment_dir, "hw2-2026-data")
output_dir <- file.path(assignment_dir, "assets/r-results")
dir.create(output_dir, recursive = TRUE, showWarnings = FALSE)

# 公共函数仅处理输出和重复使用的统计量；各题模型仍在相应章节显式拟合。
report_table <- function(x, filename) {
  print(x, row.names = FALSE)
  write.csv(x, file.path(output_dir, filename), row.names = FALSE)
  invisible(x)
}
coef_table <- function(fit) {
  z <- summary(fit)$coefficients
  data.frame(term = rownames(z), estimate = z[, 1], se = z[, 2],
             t = z[, 3], p = z[, 4], row.names = NULL)
}
model_metrics <- function(fit) {
  n <- nobs(fit)
  rss <- sum(residuals(fit)^2)
  q <- fit$rank                       # 包括截距，使用实际秩
  data.frame(n = n, q = q, RSS = rss,
             R2 = summary(fit)$r.squared,
             adjusted_R2 = summary(fit)$adj.r.squared,
             AIC_reduced = n * log(rss / n) + 2 * q,
             BIC_reduced = n * log(rss / n) + q * log(n))
}
BIC_lecture <- function(fit) model_metrics(fit)$BIC_reduced

salary <- read.csv(file.path(data_dir, "salary.csv"))
salary$rank <- factor(salary$rank, levels = c("Asst", "Assoc", "Prof"))
salary$degree <- factor(salary$degree, levels = c("Masters", "PhD"))
salary$sex <- factor(salary$sex, levels = c("Female", "Male"))
wblake <- read.csv(file.path(data_dir, "wblake.csv"))
ais <- read.csv(file.path(data_dir, "ais.csv"))
ais$Sex <- factor(ais$Sex, levels = c(0, 1))
ais_split <- read.csv(file.path(data_dir, "ais_split.csv"))
continuous_vars <- c("Ht", "Wt", "BMI", "RCC", "WCC", "Hc", "Hg", "Ferr", "SSF")
regression_vars <- c("Sex", "Ht", "Wt", "RCC", "WCC", "Hc", "Hg", "Ferr", "BMI", "SSF")

# 1. 职称与学位的主效应模型 -------------------------------------------------
cat("\n===== Problem 1: salary ~ rank + degree =====\n")
print(table(salary$rank))
print(table(salary$degree))
print(table(salary$rank, salary$degree))
fit1 <- lm(salary ~ rank + degree, data = salary)
report_table(coef_table(fit1), "problem1-coefficients.csv")
report_table(model_metrics(fit1), "problem1-summary.csv")
# 改变参照类别只改变参数化，不改变拟合值与 RSS。
salary_relevel <- salary
salary_relevel$rank <- relevel(salary_relevel$rank, ref = "Prof")
salary_relevel$degree <- relevel(salary_relevel$degree, ref = "PhD")
fit1_relevel <- lm(salary ~ rank + degree, data = salary_relevel)
stopifnot(max(abs(fitted(fit1) - fitted(fit1_relevel))) < 1e-8)

# 2. 一至五阶多项式与 BIC ---------------------------------------------------
cat("\n===== Problem 2: polynomial regression =====\n")
fits2 <- lapply(1:5, function(d) {
  lm(Length ~ poly(Scale, d, raw = TRUE), data = wblake)
})
fits2_orth <- lapply(1:5, function(d) {
  lm(Length ~ poly(Scale, d, raw = FALSE), data = wblake)
})
results2 <- do.call(rbind, lapply(1:5, function(d) {
  data.frame(degree = d, model_metrics(fits2[[d]]),
             BIC_R = BIC(fits2[[d]]),
             max_basis_fit_difference = max(abs(fitted(fits2[[d]]) - fitted(fits2_orth[[d]]))))
}))
report_table(results2, "problem2-summary.csv")
coefficients2 <- do.call(rbind, lapply(1:5, function(d) {
  data.frame(degree = d, power = 0:d, coefficient = unname(coef(fits2[[d]])))
}))
report_table(coefficients2, "problem2-coefficients.csv")
stopifnot(max(results2$max_basis_fit_difference) < 1e-8)
cat("BIC selected degree:", results2$degree[which.min(results2$BIC_R)], "\n")
scale_grid <- data.frame(Scale = seq(min(wblake$Scale), max(wblake$Scale), length.out = 300))
for (basis in c("raw", "orth")) {
  models <- if (basis == "raw") fits2 else fits2_orth
  name <- if (basis == "raw") "problem2-poly-fits.pdf" else "problem2-poly-fits-orth.pdf"
  pdf(file.path(output_dir, name), width = 9, height = 6)
  plot(wblake$Scale, wblake$Length, pch = 16, col = adjustcolor("steelblue", 0.4),
       xlab = "Scale", ylab = "Length")
  for (d in 1:5) lines(scale_grid$Scale, predict(models[[d]], scale_grid), col = d, lwd = 2)
  legend("topleft", paste("degree", 1:5), col = 1:5, lwd = 2, bty = "n")
  dev.off()
}

# 3. 回归样条、自然样条与 GCV 平滑样条 --------------------------------------
cat("\n===== Problem 3: splines =====\n")
knots3 <- quantile(wblake$Scale, c(0.25, 0.50, 0.75))
boundary3 <- range(wblake$Scale)
fit3_poly3 <- fits2[[3]]
fit3_bs <- lm(Length ~ bs(Scale, knots = knots3, Boundary.knots = boundary3, degree = 3), data = wblake)
fit3_ns <- lm(Length ~ ns(Scale, knots = knots3, Boundary.knots = boundary3), data = wblake)
# 明确保留软件默认的结点子集；all.knots=TRUE 是另一种实现设置，不混用结果。
fit3_ss <- smooth.spline(wblake$Scale, wblake$Length, cv = FALSE, all.knots = FALSE)
predictions3 <- cbind(
  cubic = predict(fit3_poly3, scale_grid),
  bs = predict(fit3_bs, scale_grid),
  ns = predict(fit3_ns, scale_grid),
  smoothing = predict(fit3_ss, x = scale_grid$Scale)$y
)
results3 <- data.frame(
  method = c("Cubic polynomial", "Cubic regression spline", "Natural cubic spline", "Smoothing spline (GCV)"),
  RSS = c(sum(resid(fit3_poly3)^2), sum(resid(fit3_bs)^2), sum(resid(fit3_ns)^2),
          sum((wblake$Length - predict(fit3_ss, x = wblake$Scale)$y)^2)),
  design_columns = c(ncol(model.matrix(fit3_poly3)), ncol(model.matrix(fit3_bs)),
                     ncol(model.matrix(fit3_ns)), NA),
  effective_df = c(fit3_poly3$rank, fit3_bs$rank, fit3_ns$rank, fit3_ss$df)
)
report_table(results3, "problem3-summary.csv")
report_table(data.frame(lambda_internal = fit3_ss$lambda, spar = fit3_ss$spar,
                        GCV = fit3_ss$cv.crit, distinct_x = length(fit3_ss$x),
                        knot_locations = length(unique(fit3_ss$fit$knot))), "problem3-smoothing.csv")
print(knots3)
print(boundary3)
pdf(file.path(output_dir, "problem3-panels.pdf"), width = 10, height = 8)
par(mfrow = c(2, 2), mar = c(4, 4, 3, 1))
for (j in 1:4) {
  plot(wblake$Scale, wblake$Length, pch = 16, col = "grey75", xlab = "Scale", ylab = "Length",
       main = results3$method[j])
  lines(scale_grid$Scale, predictions3[, j], lwd = 2, col = "#224870")
}
dev.off()
pdf(file.path(output_dir, "problem3-combined.pdf"), width = 9, height = 6)
plot(wblake$Scale, wblake$Length, pch = 16, col = "grey75", xlab = "Scale", ylab = "Length")
matlines(scale_grid$Scale, predictions3, lwd = 2, lty = 1:4, col = 1:4)
legend("topleft", results3$method, col = 1:4, lty = 1:4, lwd = 2, bty = "n")
dev.off()

# 4. 标准化 PCA 与前三个主成分回归 ------------------------------------------
cat("\n===== Problem 4: PCA and PCR =====\n")
pca <- prcomp(ais[, continuous_vars], center = TRUE, scale. = TRUE)
report_table(data.frame(variable = continuous_vars, pca$rotation[, 1:3], row.names = NULL),
             "problem4-loadings.csv")
report_table(data.frame(component = paste0("PC", 1:3),
                        t(summary(pca)$importance[, 1:3]), row.names = NULL), "problem4-variance.csv")
dat4 <- data.frame(Bfat = ais$Bfat, pca$x[, 1:3])
fit_pc <- lm(Bfat ~ PC1 + PC2 + PC3, data = dat4)
fit4_full <- lm(reformulate(continuous_vars, "Bfat"), data = ais)
report_table(coef_table(fit_pc), "problem4-coefficients.csv")
report_table(rbind(data.frame(model = "PCR3", model_metrics(fit_pc)),
                   data.frame(model = "Nine predictors", model_metrics(fit4_full))), "problem4-summary.csv")

# 5. 因子交互模型：实际秩、调整 R2、AIC、BIC ---------------------------------
cat("\n===== Problem 5: factor interactions =====\n")
sal <- data.frame(salary = salary$salary, A = salary$sex, B = salary$rank, C = salary$degree)
print(ftable(xtabs(~ A + B + C, data = sal)))
forms5 <- list(
  M0 = salary ~ 1, M1 = salary ~ A + B + C,
  M2 = salary ~ A + B + C + A:B,
  M3 = salary ~ A + B + C + B:C,
  M4 = salary ~ A + B + C + A:C,
  M5 = salary ~ A + B + C + A:B + B:C + A:C,
  M6 = salary ~ A * B * C
)
fits5 <- lapply(forms5, lm, data = sal)
results5 <- do.call(rbind, lapply(names(fits5), function(nm) {
  fit <- fits5[[nm]]
  data.frame(model = nm, model_metrics(fit), nominal_columns = ncol(model.matrix(fit)),
             aliased = sum(is.na(coef(fit))))
}))
report_table(results5, "problem5-summary.csv")
print(alias(fits5$M6))
cat("Adjusted R2 selects:", results5$model[which.max(results5$adjusted_R2)],
    "; AIC selects:", results5$model[which.min(results5$AIC_reduced)],
    "; BIC selects:", results5$model[which.min(results5$BIC_reduced)], "\n")

# 6. BIC 前向、后向、双向选择与穷举核验 -------------------------------------
cat("\n===== Problem 6: BIC selection =====\n")
ais6 <- na.omit(ais[, c("Bfat", regression_vars)])
m0 <- lm(Bfat ~ 1, data = ais6)
m1 <- lm(Bfat ~ ., data = ais6)
scope6 <- list(lower = ~ 1, upper = formula(m1))
k6 <- log(nobs(m1))
m.forward <- step(m0, scope = scope6, direction = "forward", k = k6, trace = 0)
m.backward <- step(m1, scope = scope6, direction = "backward", k = k6, trace = 0)
m.stepwise <- step(m0, scope = scope6, direction = "both", k = k6, trace = 0)
models6 <- list(FS = m.forward, BE = m.backward, Both = m.stepwise)
for (nm in names(models6)) {
  path <- as.data.frame(models6[[nm]]$anova)
  names(path)[names(path) == "AIC"] <- "BIC"
  report_table(path, paste0("problem6-path-", nm, ".csv"))
}
report_table(do.call(rbind, lapply(names(models6), function(nm) {
  data.frame(method = nm, model_metrics(models6[[nm]]))
})), "problem6-summary.csv")
report_table(coef_table(m.forward), "problem6-coefficients.csv")
# 保存逐步选择中所有关键候选表，使用与正文一致的简化 BIC。
for (j in 0:2) {
  current <- list(m0, lm(Bfat ~ SSF, data = ais6), m.forward)[[j + 1]]
  candidates6 <- as.data.frame(add1(current, scope = scope6$upper, k = k6))
  names(candidates6)[names(candidates6) == "AIC"] <- "BIC"
  candidates6 <- data.frame(operation = rownames(candidates6), candidates6, row.names = NULL)
  report_table(candidates6, paste0("problem6-add-step", j, ".csv"))
}
subsets6 <- lapply(0:(2^length(regression_vars) - 1), function(mask) {
  chosen <- regression_vars[as.logical(intToBits(mask)[seq_along(regression_vars)])]
  form <- if (length(chosen)) reformulate(chosen, "Bfat") else Bfat ~ 1
  fit <- lm(form, data = ais6)
  data.frame(variables = paste(chosen, collapse = " + "), q = fit$rank, BIC = BIC_lecture(fit))
})
subsets6 <- do.call(rbind, subsets6)
subsets6 <- subsets6[order(subsets6$BIC), ]
write.csv(subsets6, file.path(output_dir, "problem6-all-subsets.csv"), row.names = FALSE)
print(head(subsets6, 2), row.names = FALSE)
stopifnot(abs(subsets6$BIC[1] - BIC_lecture(m.forward)) < 1e-8)

# 7. 手算结果的矩阵核验（按本题目标函数，不调用 glmnet） ----------------------
cat("\n===== Problem 7: closed-form estimates =====\n")
X7 <- rbind(c(-1, 0), c(0, -1), c(0, 0), c(0, 1), c(1, 0))
Y7 <- c(3, -4, 1, 2, -2)
lambda7 <- 5
XtX7 <- crossprod(X7)
XtY7 <- drop(crossprod(X7, Y7))
beta7 <- cbind(
  OLS = solve(XtX7, XtY7),
  Ridge = solve(XtX7 + lambda7 * diag(2), XtY7),
  Lasso = sign(XtY7) * pmax(abs(XtY7) - lambda7, 0) / diag(XtX7)
)
intercept7 <- 3 - drop(c(2, -1) %*% beta7)
report_table(data.frame(method = colnames(beta7), intercept = intercept7,
                        beta1 = beta7[1, ], beta2 = beta7[2, ], row.names = NULL), "problem7-summary.csv")
print(XtX7)
print(XtY7)

# 8. 岭回归、Lasso 与预测组合 ------------------------------------------------
cat("\n===== Problem 8: ridge, lasso and prediction combination =====\n")
train_info <- ais_split[ais_split$set == "train", ]
test_info <- ais_split[ais_split$set == "test", ]
train_data <- ais[train_info$row_id, ]
test_data <- ais[test_info$row_id, ]
foldid <- train_info$fold
stopifnot(nrow(train_data) == 150, nrow(test_data) == 52, all(table(foldid) == 30),
          !anyDuplicated(ais_split$row_id), setequal(ais_split$row_id, seq_len(nrow(ais))))
x_formula <- reformulate(regression_vars)
sex_contrasts <- list(Sex = contr.treatment(c("0", "1"), base = 1))
x_train <- model.matrix(x_formula, train_data, contrasts.arg = sex_contrasts)[, -1, drop = FALSE]
x_test <- model.matrix(x_formula, test_data, contrasts.arg = sex_contrasts)[, -1, drop = FALSE]
y_train <- train_data$Bfat
y_test <- test_data$Bfat
cv_ridge <- glmnet::cv.glmnet(
  x_train, y_train, family = "gaussian", alpha = 0,
  foldid = foldid, nfolds = 5, type.measure = "mse", standardize = TRUE, intercept = TRUE
)
cv_lasso <- glmnet::cv.glmnet(
  x_train, y_train, family = "gaussian", alpha = 1,
  foldid = foldid, nfolds = 5, type.measure = "mse", standardize = TRUE, intercept = TRUE
)
# 系数和预测均在原始量纲；测试集仅用于最终评价。
coef_ridge <- as.matrix(coef(cv_ridge, s = "lambda.min"))
coef_lasso <- as.matrix(coef(cv_lasso, s = "lambda.min"))
pred_ridge <- as.numeric(predict(cv_ridge, newx = x_test, s = "lambda.min"))
pred_lasso <- as.numeric(predict(cv_lasso, newx = x_test, s = "lambda.min"))
mse_ridge <- mean((y_test - pred_ridge)^2)
mse_lasso <- mean((y_test - pred_lasso)^2)
results8 <- data.frame(
  method = c("Ridge", "Lasso"), lambda = c(cv_ridge$lambda.min, cv_lasso$lambda.min),
  cv_mse = c(min(cv_ridge$cvm), min(cv_lasso$cvm)), test_mse = c(mse_ridge, mse_lasso),
  nonzero_slopes = c(sum(coef_ridge[-1, 1] != 0), sum(coef_lasso[-1, 1] != 0))
)
report_table(results8, "problem8-summary.csv")
report_table(data.frame(term = rownames(coef_ridge), ridge = coef_ridge[, 1],
                        lasso = coef_lasso[, 1], row.names = NULL), "problem8-coefficients.csv")
omega <- seq(0, 1, by = 0.1)
combo_mse <- vapply(omega, function(w) {
  mean((y_test - (w * pred_ridge + (1 - w) * pred_lasso))^2)
}, numeric(1))
report_table(data.frame(omega, test_mse = combo_mse), "problem8-combo.csv")
# 这条测试曲线只用于题目要求的描述，不能据其最小值宣称独立调参效果。
for (method in c("ridge", "lasso")) {
  png(file.path(output_dir, paste0("problem8-", method, "-cv.png")), width = 1500, height = 1000, res = 180)
  par(mar = c(5, 5, 6, 2) + 0.1)
  plot(if (method == "ridge") cv_ridge else cv_lasso, sign.lambda = 1)
  title(main = paste(method, "5-fold CV"), line = 4)
  dev.off()
}
png(file.path(output_dir, "problem8-combo.png"), width = 1500, height = 1000, res = 180)
plot(omega, combo_mse, type = "b", pch = 19, col = "#224870",
     xlab = expression(omega), ylab = "Test MSE", main = "Ridge / Lasso prediction combination")
grid()
dev.off()

# 9. Group lasso：训练集标准化与组选择 ---------------------------------------
cat("\n===== Problem 9: group lasso =====\n")
vars9 <- c("Ht", "Wt", "BMI", "RCC", "Hc", "Hg", "WCC", "Ferr", "SSF", "Sex1")
x9_train_raw <- x_train[, vars9, drop = FALSE]
x9_test_raw <- x_test[, vars9, drop = FALSE]
y9_train <- y_train
y9_test <- y_test
foldid9 <- foldid
groupid <- c(1, 1, 1, 2, 2, 2, 3, 3, 4, 5)
group_weights <- sqrt(as.numeric(table(groupid)))
mean9 <- colMeans(x9_train_raw)
sd9 <- apply(x9_train_raw, 2, sd)       # 样本标准差，分母 n-1；包括 Sex1
stopifnot(all(is.finite(sd9)), all(sd9 > 0))
x9_train <- scale(x9_train_raw, center = mean9, scale = sd9)
x9_test <- scale(x9_test_raw, center = mean9, scale = sd9)
# 按题目约定，固定上述全训练集变换后做 CV；gglasso 1.6 的 L2 为 MSE。
cv_group <- gglasso::cv.gglasso(
  x9_train, y9_train, group = groupid, loss = "ls", pred.loss = "L2",
  foldid = foldid9, nfolds = 5, pf = group_weights, intercept = TRUE
)
lambda_group <- cv_group$lambda.min
coef_group <- as.matrix(coef(cv_group, s = "lambda.min"))
group_norms <- vapply(1:5, function(g) sqrt(sum(coef_group[-1, 1][groupid == g]^2)), numeric(1))
pred_group <- as.numeric(predict(cv_group, newx = x9_test, s = "lambda.min"))
mse_group <- mean((y9_test - pred_group)^2)
report_table(data.frame(method = "Group lasso", package_version = as.character(packageVersion("gglasso")),
                        lambda = lambda_group, cv_mse = min(cv_group$cvm), test_mse = mse_group,
                        retained_groups = paste(which(group_norms > 0), collapse = ",")), "problem9-summary.csv")
report_table(data.frame(term = c("(Intercept)", vars9), group = c(0, groupid),
                        coefficient = coef_group[, 1], row.names = NULL), "problem9-coefficients.csv")
report_table(data.frame(group = 1:5, weight = group_weights, norm = group_norms,
                        retained = group_norms > 0), "problem9-groups.csv")
write.csv(data.frame(term = vars9, mean = mean9, sample_sd = sd9),
          file.path(output_dir, "problem9-scaling.csv"), row.names = FALSE)
write.csv(data.frame(lambda = cv_group$lambda, cv_mse = cv_group$cvm),
          file.path(output_dir, "problem9-cv.csv"), row.names = FALSE)
png(file.path(output_dir, "problem9-cv.png"), width = 1500, height = 1000, res = 180)
# 手绘同一 CV 结果，避免包默认顶轴重复打印冗长的 log(lambda)。
plot(log(cv_group$lambda), cv_group$cvm, type = "b", pch = 19, cex = 0.6, col = "#224870",
     xlab = expression(log(lambda)), ylab = "CV MSE", main = "Group lasso: 5-fold CV",
     ylim = range(cv_group$cvlo, cv_group$cvup))
arrows(log(cv_group$lambda), cv_group$cvlo, log(cv_group$lambda), cv_group$cvup,
       angle = 90, code = 3, length = 0.02, col = "grey65")
abline(v = log(c(cv_group$lambda.min, cv_group$lambda.1se)), lty = c(2, 3), col = c("#224870", "#b35a25"))
legend("topleft", c("lambda.min", "lambda.1se"), lty = c(2, 3), col = c("#224870", "#b35a25"), bty = "n")
dev.off()
report_table(data.frame(method = c("Ridge", "Lasso", "Group lasso"),
                        test_mse = c(mse_ridge, mse_lasso, mse_group)), "problem9-comparison.csv")

# 运行环境：用于核对包版本及数值复现 ----------------------------------------
writeLines(capture.output(sessionInfo()), file.path(output_dir, "session-info.txt"))
cat("\n所有结果已写入：", output_dir, "\n")
