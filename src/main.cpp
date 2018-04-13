/*
 * MIT License
 *
 * Copyright (c) 2018 Alexander Chumakov
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "utils.h"

#include <QTimer>
#include <stdio.h>
#include <openssl/pem.h>
#include <openssl/x509.h>
#include <QCoreApplication>

int main(int argc, char **argv)
{
  QCoreApplication app(argc, argv);
  QTimer::singleShot(500, &app, SLOT(quit()));

  FILE *const file = fopen("../data/Geotrust_PCA_G3_Root.pem", "r");
  if (file) {
    char *name = NULL;
    char *header = NULL;
    unsigned char *data = NULL;
    long len = 0;
    int res = PEM_read(file, &name, &header, &data, &len);
    printf("Reading result: %d\n", res);
    printf("--- Name: [%s]\n", name);
    printf("--- Header: [%s]\n", header);
    printf("--- Data:\n");
    Utils::hexDump(data, len);
    printf("*****************************************************************************************************\n");
    const unsigned char *p = data;
    X509 *const x509 = d2i_X509(NULL, &p, len);
    if (x509) {
      X509_print_fp(stdout, x509);
    } else {
      fprintf(stderr, "Error: failed loading certificate\n");
    }

    /* Clean up */
    fclose(file);
  } else {
    fprintf(stderr, "Error: failed opening the file\n");
  }
  printf("*****************************************************************************************************\n");

  return app.exec();
}
