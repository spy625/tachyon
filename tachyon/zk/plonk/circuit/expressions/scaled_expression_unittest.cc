#include "tachyon/zk/plonk/circuit/expressions/scaled_expression.h"

#include "gtest/gtest.h"

#include "tachyon/math/elliptic_curves/bn/bn254/fr.h"
#include "tachyon/zk/plonk/circuit/expressions/constant_expression.h"

namespace tachyon::zk {

using Fr = math::bn254::Fr;

class ScaledExpressionTest : public testing::Test {
 public:
  static void SetUpTestSuite() { Fr::Init(); }
};

TEST_F(ScaledExpressionTest, DegreeComplexity) {
  Fr scale = Fr::One();
  std::unique_ptr<ConstantExpression<Fr>> expr =
      ConstantExpression<Fr>::CreateForTesting(Fr::One());

  size_t expr_degree = expr->Degree();
  uint64_t expr_complexity = expr->Complexity();

  std::unique_ptr<ScaledExpression<Fr>> scaled_expr =
      ScaledExpression<Fr>::CreateForTesting(std::move(expr), std::move(scale));

  EXPECT_EQ(scaled_expr->Degree(), expr_degree);
  EXPECT_EQ(scaled_expr->Complexity(),
            expr_complexity + ScaledExpression<Fr>::kOverhead);
}

}  // namespace tachyon::zk
