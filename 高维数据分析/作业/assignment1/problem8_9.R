args <- commandArgs(trailingOnly = FALSE)
script_arg <- grep("^--file=", args, value = TRUE)
base_dir <- if (length(script_arg)) {
  dirname(normalizePath(sub("^--file=", "", script_arg[1])))
} else {
  getwd()
}
out_dir <- file.path(base_dir, "assets", "r-results")
dir.create(out_dir, recursive = TRUE, showWarnings = FALSE)

# 散点图矩阵：对角线直方图与密度曲线，下三角散点及拟合线，上三角相关系数。
panel_hist <- function(x, ...) {
  usr <- par("usr")
  on.exit(par(usr = usr))
  h <- hist(x, plot = FALSE)
  d <- density(x)
  par(usr = c(usr[1:2], 0, max(h$density, d$y) * 1.15))
  rect(head(h$breaks, -1), 0, tail(h$breaks, -1), h$density,
       col = "lightblue", border = "white")
  lines(d, col = "steelblue", lwd = 2)
}
panel_scatter <- function(x, y, ...) {
  points(x, y, pch = 16, col = adjustcolor("steelblue", alpha.f = 0.5))
  abline(lm(y ~ x), col = "firebrick", lty = 2, lwd = 2)
}
panel_cor <- function(x, y, ...) {
  usr <- par("usr")
  on.exit(par(usr = usr))
  par(usr = c(0, 1, 0, 1))
  text(0.5, 0.5, sprintf("r = %.3f", cor(x, y)), cex = 1.2)
}
save_pairs <- function(data, filename) {
  png(file.path(out_dir, filename), width = 1600, height = 1600, res = 180)
  on.exit(dev.off())
  pairs(data, lower.panel = panel_scatter, upper.panel = panel_cor,
        diag.panel = panel_hist)
}
t_table <- function(model) {
  tab <- coef(summary(model))
  t_value <- tab[, "Estimate"] / tab[, "Std. Error"]
  data.frame(estimate = tab[, "Estimate"], SE = tab[, "Std. Error"],
             t_value = t_value,
             p_value = 2 * pt(-abs(t_value), df = df.residual(model)))
}

# ==================== 第8题 ====================
water <- read.csv(file.path(base_dir, "water.csv"))
water_vars <- c("BSAAM", "OPBPC", "OPRC", "OPSLAKE")
stopifnot(all(water_vars %in% names(water)), !anyNA(water[water_vars]))

# (1) 散点图矩阵与相关矩阵。
save_pairs(water[water_vars], "problem8-scatter-matrix.png")
cat("\n第8题(1)：相关矩阵\n")
print(round(cor(water[water_vars]), 3))
# 所有非对角相关系数均较大且为正，没有较大的负相关。

# (2) 多元回归摘要、t 检验和系数的95%置信区间。
fit8 <- lm(BSAAM ~ OPBPC + OPRC + OPSLAKE, data = water)
cat("\n第8题(2)：回归摘要\n")
print(summary(fit8))
print(t_table(fit8))
print(confint(fit8))
cat("t 检验自由度：", df.residual(fit8), "\n")

# ==================== 第9题 ====================
boston <- read.csv(file.path(base_dir, "Boston.csv"))
stopifnot("MEDV" %in% names(boston), !anyNA(boston))

# (1) MEDV 关于其余13个特征的回归；
fit9_full <- lm(MEDV ~ ., data = boston)
cat("\n第9题(1)：完整模型\n")
print(summary(fit9_full))
print(t_table(fit9_full))
cat("t 检验自由度：", df.residual(fit9_full), "\n")

# (2) 选择 RM、LSTAT、PTRATIO，与 MEDV 一起画散点图矩阵。
boston_vars <- c("MEDV", "RM", "LSTAT", "PTRATIO")
save_pairs(boston[boston_vars], "problem9-scatter-matrix.png")
cat("\n第9题(2)：所选变量的相关矩阵\n")
print(round(cor(boston[boston_vars]), 3))

# (3) 多重共线性：VIF_j = 1/(1-R_j^2)。
vif_numeric <- function(model) {
  x <- model.matrix(model)[, -1, drop = FALSE]
  values <- vapply(seq_len(ncol(x)), function(j) {
    auxiliary <- lm(x[, j] ~ x[, -j, drop = FALSE])
    1 / (1 - summary(auxiliary)$r.squared)
  }, numeric(1))
  setNames(values, colnames(x))
}
cat("\n第9题(3)：完整模型的 VIF\n")
vif_full <- vif_numeric(fit9_full)
print(sort(vif_full, decreasing = TRUE))
# VIF > 5 提示值得关注，> 10 常被视为严重；阈值只是经验标准。
cat("RAD 与 TAX 的相关系数：", cor(boston$RAD, boston$TAX), "\n")

fit9_no_RAD <- update(fit9_full, . ~ . - RAD)
fit9_no_TAX <- update(fit9_full, . ~ . - TAX)
fit9_no_both <- update(fit9_full, . ~ . - RAD - TAX)
fit9_no_AGE_INDUS <- update(fit9_full, . ~ . - AGE - INDUS)
models <- list(full = fit9_full,
               without_RAD = fit9_no_RAD,
               without_TAX = fit9_no_TAX,
               without_both = fit9_no_both,
               without_AGE_INDUS = fit9_no_AGE_INDUS)
for (name in names(models)[-1]) {
  cat("\n简化模型的回归摘要：", name, "\n")
  print(summary(models[[name]]))
}

# 按全模型的变量顺序对齐各模型的 VIF。
vif_comparison <- as.data.frame(lapply(models, function(model) {
  vif_numeric(model)[names(vif_full)]
}))
rownames(vif_comparison) <- names(vif_full)
cat("\n各模型的 VIF（NA 表示该变量已删除）\n")
print(round(vif_comparison, 3))

model_metrics <- function(model) {
  s <- summary(model)
  v <- vif_numeric(model)
  c(n = nobs(model), R_squared = s$r.squared,
    adjusted_R_squared = s$adj.r.squared,
    residual_SE = s$sigma, AIC = AIC(model), BIC = BIC(model),
    F_statistic = unname(s$fstatistic["value"]),
    VIF_RAD = unname(v["RAD"]),
    VIF_TAX = unname(v["TAX"]), max_VIF = max(v))
}
comparison <- t(sapply(models, model_metrics))
cat("\n模型拟合指标与 VIF 汇总（NA 表示该变量已删除）\n")
print(round(comparison, 4))
for (name in names(models)[-1]) {
  cat("\n嵌套模型 F 检验：", name, " 与全模型比较\n")
  print(anova(models[[name]], fit9_full))
}

write.csv(comparison, file.path(out_dir, "problem9-model-comparison.csv"))
write.csv(vif_comparison, file.path(out_dir, "problem9-vif-comparison.csv"))
cat("\n图片和比较表已保存至：", out_dir, "\n")
