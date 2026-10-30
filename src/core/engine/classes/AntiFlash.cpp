#include "AntiFlash.hpp"

#include "config/Current.hpp"
#include "core/engine/Engine.hpp"
#include "core/offsets/Offsets.hpp"

void AntiFlash::Tick()
{
    if (!cfg::settings::anti_flash)
        return;

    auto process = Engine::GetProcess();
    if (!process || !process->handle_)
        return;

    auto client = Engine::GetClient();
    if (!client.base)
        return;

    const auto controller = process->read<uintptr_t>(client.base + offsets::localPlayerController);
    if (!controller)
        return;

    const auto entity_list = process->read<uintptr_t>(client.base + offsets::entityList);
    if (!entity_list)
        return;

    const auto pawn_handle = process->read<uint32_t>(controller + offsets::controller::m_hPawn);
    if (!pawn_handle)
        return;

    const auto pawn_list_entry = process->read<uintptr_t>(
        entity_list + 0x10 + 0x8 * ((pawn_handle & 0x7FFF) >> 9));
    if (!pawn_list_entry)
        return;

    const auto pawn = process->read<uintptr_t>(pawn_list_entry + 0x70 * (pawn_handle & 0x1FF));
    if (!pawn)
        return;

    const float alpha = process->read<float>(pawn + offsets::pawn::m_flFlashOverlayAlpha);
    if (alpha > 0.f)
        process->write<float>(pawn + offsets::pawn::m_flFlashOverlayAlpha, 0.f);

    const float duration = process->read<float>(pawn + offsets::pawn::m_flFlashDuration);
    if (duration > 0.f)
        process->write<float>(pawn + offsets::pawn::m_flFlashDuration, 0.f);
}
