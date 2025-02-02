/*
 * Copyright (c) 2022-2023 The University of Edinburgh
 * All rights reserved
 *
 * The license below extends only to copyright in the software and shall
 * not be construed as granting a license to any other intellectual
 * property including but not limited to intellectual property relating
 * to a hardware implementation of the functionality of the software
 * licensed hereunder.  You may use the software subject to the license
 * terms below provided that you ensure that this notice is replicated
 * unmodified and in its entirety in all distributions of the software,
 * modified or unmodified, in source code or in binary form.
 *
 * Copyright (c) 2004-2005 The Regents of The University of Michigan
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met: redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer;
 * redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution;
 * neither the name of the copyright holders nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "cpu/pred/btb.hh"

namespace gem5
{

    namespace branch_prediction
    {

        BranchTargetBuffer::BranchTargetBuffer(const Params &params)
            : ClockedObject(params),
              numThreads(params.numThreads),
              stats(this)
        {
        }

        const StaticInstPtr
        BranchTargetBuffer::lookupInst(ThreadID tid, Addr instPC)
        {
            panic("Not implemented for this BTB");
            return nullptr;
        }

        BranchTargetBuffer::BranchTargetBufferStats::BranchTargetBufferStats(
            statistics::Group *parent)
            : statistics::Group(parent),
              ADD_STAT(lookups, statistics::units::Count::get(),
                       "Number of BTB lookups"),
              ADD_STAT(lookupType, statistics::units::Count::get(),
                       "Number of BTB lookups per branch type"),
              ADD_STAT(misses, statistics::units::Count::get(),
                       "Number of BTB misses"),
              ADD_STAT(missType, statistics::units::Count::get(),
                       "Number of BTB misses per branch type"),
              ADD_STAT(missRatio, statistics::units::Ratio::get(), "BTB Hit Ratio",
                       misses / lookups),
              ADD_STAT(updates, statistics::units::Count::get(),
                       "Number of BTB updates"),
              ADD_STAT(mispredict, statistics::units::Count::get(),
                       "Number of BTB mispredicts"),
              ADD_STAT(evictions, statistics::units::Count::get(),
                       "Number of BTB evictions")
        {
            using namespace statistics;
            missRatio.precision(6);
            lookupType
                .init(enums::Num_BranchType)
                .flags(total | pdf);

            missType
                .init(enums::Num_BranchType)
                .flags(total | pdf);

            updates
                .init(enums::Num_BranchType)
                .flags(total | pdf);

            mispredict
                .init(enums::Num_BranchType)
                .flags(total | pdf);

            evictions.flags(nozero);

            for (int i = 0; i < enums::Num_BranchType; i++)
            {
                lookupType.subname(i, enums::BranchTypeStrings[i]);
                missType.subname(i, enums::BranchTypeStrings[i]);
                updates.subname(i, enums::BranchTypeStrings[i]);
                mispredict.subname(i, enums::BranchTypeStrings[i]);
            }
        }

    } // namespace branch_prediction
} // namespace gem5
