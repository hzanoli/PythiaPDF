#include "base/pdfplot.h"
#include "gtest/gtest.h"

namespace ppb = pythiapdf::base;

TEST(TestPDFPlot, HistogramTitles) {
  ASSERT_EQ(ppb::PDFPlot("SomePDF", 100.).Histogram().GetTitle(),
            "SomePDF F(x, Q2=100) GeV/c")
      << "The histogram title is not set correctly.";
}