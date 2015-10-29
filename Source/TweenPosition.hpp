#pragma once

#include "Tweener.hpp"

/// <summary>
/// Defines a tween component that only affects a GameObject's position.
/// </summary>
class TweenPosition : public Tweener
{
public:
    /// <summary>
    /// Creates a new tween position component.
    /// </summary>
    TweenPosition( GameObject* gameObject );

    /// <summary>
    /// Gets the starting position value.
    /// </summary>
    DirectX::XMFLOAT3 GetStartValue() const;

    /// <summary>
    /// Gets the ending position value.
    /// </summary>
    DirectX::XMFLOAT3 GetEndValue() const;

    /// <summary>
    /// Sets the starting position value.
    /// </summary>
    /// <param name="value">The new starting value.</param>
    void SetStartValue( const DirectX::XMFLOAT3& value );

    /// <summary>
    /// Sets the ending position value.
    /// </summary>
    /// <param name="value">The new ending value.</param>
    void SetEndValue( const DirectX::XMFLOAT3& value );

    /// <summary>
    /// Updates this tween position component.
    /// </summary>
    /// <param name="gameTime">Provides a snapshot of timing values.</param>
    void Update( const GameTime& gameTime ) override;
};