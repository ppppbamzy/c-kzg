/*
 * Copyright 2021 Benjamin Edgington
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "fft_common.h"
#include "blst_util.h"
#include "c_kzg_util.h"

bool is_power_of_two(const uint64_t n) {
    return (n & (n - 1)) == 0;
}

// Create an array of powers of the root of unity
// The `out` array must be of size `width + 1`
C_KZG_RET expand_root_of_unity(blst_fr *roots, const blst_fr *root_of_unity, const uint64_t width) {
    roots[0] = fr_one;
    roots[1] = *root_of_unity;

    for (uint64_t i = 2; !fr_is_one(&roots[i - 1]); i++) {
        ASSERT(i <= width, C_KZG_ERROR);
        blst_fr_mul(&roots[i], &roots[i - 1], root_of_unity);
    }
    ASSERT(fr_is_one(&roots[width]), C_KZG_ERROR);

    return C_KZG_OK;
}

// Create a reversed list of Fr provided
// `width` is one less than the length of `roots`
C_KZG_RET reverse(blst_fr *out, const blst_fr *roots, const uint64_t width) {
   for (uint64_t i = 0; i <= width; i++) {
       out[i] = roots[width - i];
   }

   return C_KZG_OK;
}

C_KZG_RET new_fft_settings(FFTSettings *fs, const unsigned int max_scale) {
    C_KZG_RET ret;
    fs->max_width = (uint64_t)1 << max_scale;
    blst_fr_from_uint64(&fs->root_of_unity, scale2_root_of_unity[max_scale]);

    ASSERT(c_kzg_malloc((void **)&fs->expanded_roots_of_unity, (fs->max_width + 1) * sizeof(blst_fr)) == C_KZG_OK, C_KZG_MALLOC);
    ASSERT(c_kzg_malloc((void **)&fs->reverse_roots_of_unity, (fs->max_width + 1) * sizeof(blst_fr)) == C_KZG_OK, C_KZG_MALLOC);

    ret = expand_root_of_unity(fs->expanded_roots_of_unity, &fs->root_of_unity, fs->max_width);
    if (ret != C_KZG_OK) return ret;
    ret = reverse(fs->reverse_roots_of_unity, fs->expanded_roots_of_unity, fs->max_width);
    return ret;
}

void free_fft_settings(FFTSettings *fs) {
    free(fs->expanded_roots_of_unity);
    free(fs->reverse_roots_of_unity);
}
