classdef LinescanAttribute < TftpAttribute
    %LinescanAttribute 
    
    properties (Constant)

    end
 
    methods
        % LinescanAttribute constructor
        function obj = LinescanAttribute(code, attribute)
            % set default properties used in superclass constructor
            fsize = 256;
            ctype = 'uint16';
            mtype = 'single';
            
            % call TftpAttribute constructor
            obj = obj@TftpAttribute(code, attribute, fsize, ctype, mtype);      
        end
        
        % decode
        function value = decode(obj, value)
            % cast byte stream
            value = decode@TftpAttribute(obj, value);
            % normalise
            value = cast(value, obj.mtype);
            value = value/65535;
            value = transpose(value); % rotate to fit in TftpRecord properly
        end
        
        % encode
        function value = encode(obj, value)
            % denormalise
            value = transpose(value); % derotate
            value = value*65535;
            value = cast(value, obj.ctype);  
            % cast to byte stream
            value = encode@TftpAttribute(obj, value);
        end
    end   
end