/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "unknown/utility/brave_content_utility_client.h"

#include <memory>
#include <utility>

#include "unknown/components/brave_wallet/common/buildflags/buildflags.h"
#include "unknown/components/services/bat_ads/bat_ads_service_impl.h"
#include "unknown/components/services/bat_ads/public/interfaces/bat_ads.mojom.h"
#include "unknown/components/services/bat_rewards/public/interfaces/rewards_engine_factory.mojom.h"
#include "unknown/components/services/bat_rewards/rewards_engine_factory.h"
#include "unknown/components/tor/buildflags/buildflags.h"
#include "mojo/public/cpp/bindings/service_factory.h"

#if !BUILDFLAG(IS_ANDROID)
#include "unknown/utility/importer/brave_profile_import_impl.h"
#endif

#if BUILDFLAG(ENABLE_TOR)
#include "unknown/components/services/tor/public/interfaces/tor.mojom.h"
#include "unknown/components/services/tor/tor_launcher_impl.h"
#endif

#if BUILDFLAG(ENABLE_BRAVE_WALLET)
#include "unknown/components/services/brave_wallet/brave_wallet_utils_service_impl.h"
#include "unknown/components/services/brave_wallet/public/mojom/brave_wallet_utils_service.mojom.h"
#endif

namespace {

#if !BUILDFLAG(IS_ANDROID)
auto RunBraveProfileImporter(
    mojo::PendingReceiver<brave::mojom::ProfileImport> receiver) {
  return std::make_unique<BraveProfileImportImpl>(std::move(receiver));
}
#endif

#if BUILDFLAG(ENABLE_TOR)
auto RunTorLauncher(mojo::PendingReceiver<tor::mojom::TorLauncher> receiver) {
  return std::make_unique<tor::TorLauncherImpl>(std::move(receiver));
}
#endif

auto RunRewardsEngineFactory(
    mojo::PendingReceiver<brave_rewards::mojom::RewardsEngineFactory>
        receiver) {
  return std::make_unique<brave_rewards::internal::RewardsEngineFactory>(
      std::move(receiver));
}

auto RunBatAdsService(
    mojo::PendingReceiver<bat_ads::mojom::BatAdsService> receiver) {
  return std::make_unique<bat_ads::BatAdsServiceImpl>(std::move(receiver));
}

#if BUILDFLAG(ENABLE_BRAVE_WALLET)
auto RunBraveWalletUtilsService(
    mojo::PendingReceiver<brave_wallet::mojom::BraveWalletUtilsService>
        receiver) {
  return std::make_unique<brave_wallet::BraveWalletUtilsServiceImpl>(
      std::move(receiver));
}
#endif

}  // namespace

BraveContentUtilityClient::BraveContentUtilityClient() = default;
BraveContentUtilityClient::~BraveContentUtilityClient() = default;

void BraveContentUtilityClient::RegisterMainThreadServices(
    mojo::ServiceFactory& services) {
#if !BUILDFLAG(IS_ANDROID)
  services.Add(RunBraveProfileImporter);
#endif

#if BUILDFLAG(ENABLE_TOR)
  services.Add(RunTorLauncher);
#endif

  services.Add(RunRewardsEngineFactory);

  services.Add(RunBatAdsService);

#if BUILDFLAG(ENABLE_BRAVE_WALLET)
  services.Add(RunBraveWalletUtilsService);
#endif

  return ChromeContentUtilityClient::RegisterMainThreadServices(services);
}
