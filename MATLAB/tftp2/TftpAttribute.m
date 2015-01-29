classdef TftpAttribute
    %TftpAttribute
    
    properties
        code      = uint16.empty;
        attribute = char.empty;   % attribute name
        ctype     = char.empty;   % native data type
        mtype     = char.empty;   % convenient MATLAB data type
    end
    
    methods
        % TftpAttribute constructor
        function obj = TftpAttribute(code, attribute, ctype, mtype)
            % parse input
            p = inputParser();
            addRequired(p, 'code', @ischar);
            addRequired(p, 'attribute', @ischar);
            addRequired(p, 'ctype', @ischar);
            addRequired(p, 'mtype', @ischar);
            parse(p, code, attribute, ctype, mtype);
            
            % set properties
            obj.code      = cast(hex2dec(p.Results.code), 'uint16');
            obj.attribute = cast(p.Results.attribute, 'char');
            obj.ctype     = cast(p.Results.ctype, 'char');
            obj.mtype     = cast(p.Results.mtype, 'char');
        end
        
        % convert from bytes to ctype
        function value = decode(obj, value)

            value = typecast(value, obj.ctype); % cast bytes to ctype
            if ~strcmp(obj.ctype, obj.mtype)    
                value = cast(value, obj.mtype); % cast to mtype
            end
        end
        
        % convert from ctype to bytes
        function value = encode(obj, value)
            
            value = cast(value, obj.ctype);   % cast to ctype
            value = typecast(value, 'uint8'); % cast to bytes
        end       
    end
end

