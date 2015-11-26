using UnityEngine;
using UnityEditor;
using System.Reflection;
using System;

[AttributeUsage(AttributeTargets.Field)]
public class PruebaAtributo1 : Attribute
{
    public readonly Vector2 position;

    public PruebaAtributo1(int x, int y)
    {
        position.x = x;
        position.y = y;
    }
}